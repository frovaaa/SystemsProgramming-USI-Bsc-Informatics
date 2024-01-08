/**
 * Frova Davide
 * Bachelor of Science in Informatics
 * Universita' della Svizzera Italiana (USI)
 * Assignment 1 - Systems Programming - 2023 Autumn semester
 *
 * For the realization of this assignment I used the following resources:
 * - PNG specification: https://www.w3.org/TR/2023/CR-png-3-20230921/
 * - CRC32 functions: https://www.w3.org/TR/2023/CR-png-3-20230921/#samplecrc
 * - Github Copilot Chat: Used only as a Q&A resource, if any code is taken from there it is indicated in the comments
 * - Hex editor: https://hexed.it/
 * - cppreference.com: https://en.cppreference.com/w/c
 * - ChatGPT: Used to analyze and understand the PNG specification in a simpler way,
 *            if reading the specification directly was not enough / completely clear
 *
 * If any other resource is used, it is indicated in the comments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data Structures
struct image
{
    const char *filename;
    unsigned width;
    unsigned height;
    unsigned bit_depth;
    unsigned color_type;
    unsigned num_chunks;
    struct chunk *chunks;
    unsigned num_keywords;
    struct keyword *keywords;
    unsigned int valid;
};

struct chunk
{
    struct chunk *next;

    unsigned sequence_number;
    unsigned int length;
    unsigned char *type;
    unsigned char *data;
    unsigned crc;
};

struct keyword
{
    struct keyword *next;

    char *keyword;
    char *text;
};

// Default format string
char pformat[1000] = "_f: _w x _h, _c, _d bits per sample, _N chunks\n_C\n_K";
char cformat[1000] = "\t_n: _t (_l)\n";
char kformat[1000] = "\t_k: _t\n";

// Correct chunk types
unsigned char chunk_type_ihdr[] = {
    0x49, 0x48, 0x44, 0x52};
unsigned char chunk_type_plte[] = {
    0x50, 0x4c, 0x54, 0x45};
unsigned char chunk_type_idat[] = {
    0x49, 0x44, 0x41, 0x54};
unsigned char chunk_type_iend[] = {
    0x49, 0x45, 0x4e, 0x44};
unsigned char chunk_type_text[] = {
    0x74, 0x45, 0x58, 0x74};

// Correct PNG signature
unsigned char png_signature[] = {
    0x89, 0x50, 0x4e, 0x47,
    0x0d, 0x0a, 0x1a, 0x0a};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// METHODS SIGNATURES (PROTOTYPES)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Methods to verify the DATA read from the IDAT chunks
void read_ihdr_data(struct image *current_image, struct chunk *current_chunk);

// Methods to print the data in a formatted manner
void print_formatted_keywords(const struct keyword *starting_keyword);
void print_formatted_chunks(const struct chunk *starting_chunk);
void print_formatted_data(const struct image current_image);
void free_everything(struct image *current_image);

// Helper methods
char *get_color_type(unsigned int color_type);
const char *get_chunk_type_name(unsigned char *chunk_type);
int get_chunk_type(unsigned char *chunk_type);
void parse_text_data(struct image *current_image, struct chunk *current_chunk);

// CRC32 methods
void make_crc_table(void);
unsigned long update_crc(unsigned long crc, const unsigned char *buf,
                         unsigned int len);

int main(int argc, char *argv[])
{
    // Check for the minimum number of arguments
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int all_names = 0;
    struct image current_image;

    // We read the arguments
    for (unsigned i = 1; i < argc; i++)
    {
        // OPTIONS

        if (!all_names)
        {
            // Check if the current argument matches one of the formatting strings options
            if (strncmp(argv[i], "c=", 2) == 0)
            {
                memccpy(cformat, argv[i] + 2, 0, 1000);
                continue;
            }
            else if (strncmp(argv[i], "k=", 2) == 0)
            {
                memccpy(kformat, argv[i] + 2, 0, 1000);
                continue;
            }
            else if (strncmp(argv[i], "p=", 2) == 0)
            {
                memccpy(pformat, argv[i] + 2, 0, 1000);
                continue;
            }
            else if (strcmp(argv[i], "--") == 0)
            {
                all_names = 1;
                continue;
            }
        }

        // Foreach of the file name I will add a new image to the list
        // But first I initialize the struct image with default values
        current_image.filename = argv[i];
        current_image.width = 0;
        current_image.height = 0;
        current_image.bit_depth = 0;
        current_image.color_type = 0;
        current_image.num_chunks = 0;
        current_image.chunks = NULL;
        current_image.num_keywords = 0;
        current_image.keywords = NULL;
        current_image.valid = 1;

        // Open file
        FILE *fp = fopen(current_image.filename, "rb");

        if (!fp)
        {
            printf("Error: cannot open file %s\n", current_image.filename);
            current_image.valid = 0;
            goto END;
        }

        // READ THE FILE

        // Buffer to read 8 bytes from file
        unsigned char buf[8] = {0x00};

        // PNG SIGNATURE (8 bytes, always the same, required)

        // We read the first 8 bytes as the PNG signature
        // which should always be the same: 89 50 4e 47 0d 0a 1a 0a
        fread(buf, 1, 8, fp);

        // Check if the signature is correct
        // memcmp returns 0 if the two buffers are equal
        if (memcmp(buf, png_signature, 8) != 0)
        {
            fprintf(stderr, "Error: incorrect PNG signature\n");
            current_image.valid = 0;
            goto END;
        }

        // Now we start reading the chunks
        // Each chunk has the following structure:
        // 4 bytes: length of the chunk
        // 4 bytes: chunk type
        // n bytes: chunk data | Only if length > 0
        // 4 bytes: CRC32 checksum of the chunk data

        struct chunk *current_chunk = NULL;

        int valid_chunk = 1;
        int started_idat = 0;
        int prev_chunk_type = -1;

        do
        {
            struct chunk *new_chunk = malloc(sizeof(struct chunk));
            if (new_chunk == NULL)
            {
                fprintf(stderr, "Error: cannot allocate memory for chunk\n");
                current_image.valid = 0;
                valid_chunk = 0;
                goto END;
            }
            // Add the new chunk to the list
            if (current_chunk == NULL)
            {
                current_chunk = new_chunk;
                current_image.chunks = current_chunk;
            }
            else
            {
                current_chunk->next = new_chunk;
            }
            current_chunk = new_chunk;

            // Increase the chunks counter
            current_image.num_chunks++;
            current_chunk->sequence_number = current_image.num_chunks;

            // Initialize the chunk with default values
            current_chunk->next = NULL;
            current_chunk->length = 0;
            current_chunk->type = malloc(4);
            if (current_chunk->type == NULL)
            {
                fprintf(stderr, "Error: cannot allocate memory for chunk type\n");
                // Free the memory
                free(current_chunk);
                current_image.valid = 0;
                valid_chunk = 0;
                goto END;
            }
            current_chunk->data = NULL;
            current_chunk->crc = 0;

            //            printf("Chunk number: %d\n", current_image.num_chunks);

            // Read the length of the chunk (4 bytes)
            fread(buf, 1, 4, fp);
            // Thanks to Copilot for the quick way of converting 4 bytes to an unsigned int
            unsigned int chunk_length = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];

            // Update the chunk length
            current_chunk->length = chunk_length;
            //            printf("Chunk length: %d\n", chunk_length);

            // Read the chunk type (4 bytes)
            fread(buf, 1, 4, fp);
            // Save the chunk type
            memccpy(current_chunk->type, buf, 0, 4);

            // printf("Chunk type: %s\n", get_chunk_type_name(current_chunk->type));

            if (chunk_length != 0)
            {
                // Allocate the memory for the chunk data
                unsigned char *data = malloc(chunk_length);

                if (data == NULL)
                {
                    fprintf(stderr, "Error: cannot allocate memory for chunk data\n");
                    // Free the memory
                    free(current_chunk->type);
                    free(current_chunk);
                    current_image.valid = 0;
                    valid_chunk = 0;
                    goto END;
                }
                else
                {
                    current_chunk->data = data;
                }

                // Read the data of the chunk and save it in the data buffer
                fread(data, 1, chunk_length, fp);
            }

            // Read the CRC32 checksum (4 bytes)
            fread(buf, 1, 4, fp);

            // Now we need to check the CRC of the chunk
            // Removed the long from the type otherwise I was getting ffffffff9db781ec instad of just 9db781ec
            unsigned read_crc = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];

            /**
             * CREDITS: Thanks to Lamberto Ragnolini for the explanation of the code snippet below to check the CRC checksum
             * This will check the CRC in 2 steps: first it will calculate the CRC of the type and then it will update
             * it with the data part of the chunk
             * Then it will check if the calculated CRC is equal to the one read from the file
             */

            unsigned computed_crc = update_crc(0xffffffffUL, current_chunk->type, 4);

            computed_crc = update_crc(computed_crc, current_chunk->data, current_chunk->length);
            computed_crc ^= 0xffffffffUL;

            // Now we compare the calculated CRC with the one read from the file
            if (computed_crc != read_crc)
            {
                fprintf(stderr, "Error: incorrect CRC checksum\n");
                // Free the memory
                free(current_chunk->type);
                free(current_chunk->data);
                free(current_chunk);
                current_image.valid = 0;
                valid_chunk = 0;
                goto END;
            }
            else
            {
                current_chunk->crc = read_crc;
            }

            int current_chunk_type = get_chunk_type(current_chunk->type);

            // Check the validity of the chunks
            switch (current_chunk_type)
            {
            case 0:
                read_ihdr_data(&current_image, current_chunk);
                break;
            case 1:
                // Validation of PLTE chunk
                if (current_image.color_type == 0 || current_image.color_type == 4)
                {
                    fprintf(stderr, "Error: PLTE chunk not allowed for color type %s\n", get_color_type(current_image.color_type));
                    current_image.valid = 0;
                    valid_chunk = 0;
                    goto END;
                }
                break;
            case 2:
                if (started_idat == 1 && prev_chunk_type != 2)
                {
                    fprintf(stderr, "Error: IDAT chunk intervened by another chunk\n");
                    current_image.valid = 0;
                    valid_chunk = 0;
                    goto END;
                }
                else
                {
                    started_idat = 1;
                }
                break;
            case 3:
                // No need to check for IEND validation
                break;
            case 4:
                // Save the text data
                parse_text_data(&current_image, current_chunk);
                break;
            default:
                continue;
            }

            // If the current chunk is not valid, we can stop reading the file
            if (current_image.valid == 0)
            {
                valid_chunk = 0;
                goto END;
            }

            // Update the previous chunk type
            prev_chunk_type = current_chunk_type;

        } while (get_chunk_type(current_chunk->type) != 3 && valid_chunk == 1);

    END:
        // If the current image is valid, we can print the data
        if (current_image.valid == 1)
        {
            // Print all the data in a formatted manner following the formatting strings
            print_formatted_data(current_image);
        }

        free_everything(&current_image);

        // close file
        fclose(fp);
    }
}

// Methods to print the data in a formatted manner
void print_formatted_data(const struct image current_image)
{
    // Formatted printing
    // pformat
    char *pformat_pointer = pformat;
    while (*pformat_pointer != '\0')
    {
        if (*pformat_pointer == '_')
        {
            pformat_pointer++;
            switch (*pformat_pointer)
            {
            case 'f':
                printf("%s", current_image.filename);
                break;
            case 'w':
                printf("%d", current_image.width);
                break;
            case 'h':
                printf("%d", current_image.height);
                break;
            case 'd':
                printf("%d", current_image.bit_depth);
                break;
            case 'c':
                printf("%s", get_color_type(current_image.color_type));
                break;
            case 'N':
                printf("%d", current_image.num_chunks);
                break;
            case 'C':
                // Print the chunks in a formatted manner
                print_formatted_chunks(current_image.chunks);
                break;
            case 'K':
                // Print the keywords in a formatted manner
                print_formatted_keywords(current_image.keywords);
                break;
            default:
                printf("%c", *pformat_pointer);
                break;
            }
        }
        else
        {
            printf("%c", *pformat_pointer);
        }
        pformat_pointer++;
    }
}

void print_formatted_keywords(const struct keyword *starting_keyword)
{
    while (starting_keyword != NULL)
    {
        char *kformat_pointer = kformat;
        while (*kformat_pointer != '\0')
        {
            if (*kformat_pointer == '_')
            {
                kformat_pointer++;
                switch (*kformat_pointer)
                {
                case 'k':
                    printf("%s", starting_keyword->keyword);
                    break;
                case 't':
                    printf("%s", starting_keyword->text);
                    break;
                default:
                    printf("%c", *kformat_pointer);
                    break;
                }
            }
            else
            {
                printf("%c", *kformat_pointer);
            }
            kformat_pointer++;
        }
        starting_keyword = starting_keyword->next;
    }
}

void print_formatted_chunks(const struct chunk *starting_chunk)
{
    while (starting_chunk != NULL)
    {
        char *cformat_pointer = cformat;
        while (*cformat_pointer != '\0')
        {
            if (*cformat_pointer == '_')
            {
                cformat_pointer++;
                switch (*cformat_pointer)
                {
                case 'n':
                    printf("%d", starting_chunk->sequence_number);
                    break;
                case 't':
                    printf("%s", get_chunk_type_name(starting_chunk->type));
                    break;
                case 'l':
                    printf("%d", starting_chunk->length);
                    break;
                case 'c':
                    printf("%08x", starting_chunk->crc);
                    break;
                case 'D':
                    // Print the data of the chunk
                    for (unsigned i = 0; i < starting_chunk->length; i++)
                    {
                        if (i % 16 == 0 && i != 0)
                            printf("\n");
                        printf("%02x ", starting_chunk->data[i]);
                    }
                    break;
                default:
                    printf("%c", *cformat_pointer);
                    break;
                }
            }
            else
            {
                printf("%c", *cformat_pointer);
            }
            cformat_pointer++;
        }
        starting_chunk = starting_chunk->next;
    }
}

// Method to get the color type as a string
char *get_color_type(unsigned int color_type)
{
    switch (color_type)
    {
    case 0:
        return "Greyscale";
    case 2:
        return "Truecolor";
    case 3:
        return "Indexed";
    case 4:
        return "Greyscale+alpha";
    case 6:
        return "Truecolor+alpha";
    default:
        return "Unknown";
    }
}

// Method to get the chunk type as a string
const char *get_chunk_type_name(unsigned char *chunk_type)
{
    if (memcmp(chunk_type, chunk_type_ihdr, 4) == 0)
    {
        return "IHDR";
    }
    else if (memcmp(chunk_type, chunk_type_plte, 4) == 0)
    {
        return "PLTE";
    }
    else if (memcmp(chunk_type, chunk_type_idat, 4) == 0)
    {
        return "IDAT";
    }
    else if (memcmp(chunk_type, chunk_type_iend, 4) == 0)
    {
        return "IEND";
    }
    else if (memcmp(chunk_type, chunk_type_text, 4) == 0)
    {
        return "tEXt";
    }
    else
    {
        return chunk_type;
    }
}

// Method to get the chunk type as a int (we will use it in a switch)
int get_chunk_type(unsigned char *chunk_type)
{
    if (memcmp(chunk_type, chunk_type_ihdr, 4) == 0)
        return 0; // "IHDR";
    else if (memcmp(chunk_type, chunk_type_plte, 4) == 0)
        return 1; // "PLTE";
    else if (memcmp(chunk_type, chunk_type_idat, 4) == 0)
        return 2; // "IDAT";
    else if (memcmp(chunk_type, chunk_type_iend, 4) == 0)
        return 3; // "IEND";
    else if (memcmp(chunk_type, chunk_type_text, 4) == 0)
        return 4; // "tEXt";
    else
        return -1; // "Unknown";
}

// Method to read the IHDR data and validate it
void read_ihdr_data(struct image *current_image, struct chunk *current_chunk)
{
    // Read the width (4 bytes)
    unsigned char *buf = current_chunk->data;
    current_image->width = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
    if (current_image->width <= 0)
    {
        fprintf(stderr, "Error: incorrect IHDR width\n");
        current_image->valid = 0;
        return;
    }

    // Read the height (4 bytes)
    buf += 4;
    current_image->height = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
    if (current_image->height <= 0)
    {
        fprintf(stderr, "Error: incorrect IHDR height\n");
        current_image->valid = 0;
        return;
    }

    // Read the bit depth (1 byte)
    buf += 4;
    current_image->bit_depth = buf[0];
    if (current_image->bit_depth != 1 && current_image->bit_depth != 2 && current_image->bit_depth != 4 &&
        current_image->bit_depth != 8 && current_image->bit_depth != 16)
    {
        fprintf(stderr, "Error: incorrect IHDR bit depth\n");
        current_image->valid = 0;
        return;
    }

    // Read the color type (1 byte)
    buf += 1;
    current_image->color_type = buf[0];
    if (current_image->color_type != 0 && current_image->color_type != 2 && current_image->color_type != 3 &&
        current_image->color_type != 4 && current_image->color_type != 6)
    {
        fprintf(stderr, "Error: incorrect IHDR color type\n");
        current_image->valid = 0;
        return;
    }

    // Read the compression method (1 byte)
    buf += 1;
    unsigned int temp_compression_method = buf[0];
    if (temp_compression_method != 0)
    {
        fprintf(stderr, "Error: incorrect IHDR compression method\n");
        current_image->valid = 0;
        return;
    }

    // Read the filter method (1 byte)
    buf += 1;
    unsigned int temp_filter_method = buf[0];
    if (temp_filter_method != 0)
    {
        fprintf(stderr, "Error: incorrect IHDR filter method\n");
        current_image->valid = 0;
        return;
    }

    // Read the interlace method (1 byte)
    buf += 1;
    unsigned int temp_interlace_method = buf[0];
    if (temp_interlace_method != 0 && temp_interlace_method != 1)
    {
        fprintf(stderr, "Error: incorrect IHDR interlace method\n");
        current_image->valid = 0;
        return;
    }
    return;

ERROR:
    current_image->valid = 0;
    return;
}

// Method to read the text chunk data and save it
void parse_text_data(struct image *current_image, struct chunk *current_chunk)
{
    // Read the keyword until the null separator
    unsigned char *buf = current_chunk->data;
    unsigned int keyword_length = 0;
    while (buf[keyword_length] != '\0')
    {
        keyword_length++;
    }
    char *keyword = malloc(keyword_length + 1);
    if (keyword == NULL)
    {
        fprintf(stderr, "Error: cannot allocate memory for keyword\n");
        current_image->valid = 0;
        return;
    }
    memccpy(keyword, buf, 0, keyword_length + 1);

    // Read the text until the chunk length
    buf += keyword_length + 1;
    unsigned int text_length = current_chunk->length - keyword_length - 1;
    char *text = malloc(text_length + 1);
    if (text == NULL)
    {
        fprintf(stderr, "Error: cannot allocate memory for text\n");
        current_image->valid = 0;
        return;
    }
    memccpy(text, buf, 0, text_length + 1);

    // Allocate the memory for the new keyword
    struct keyword *new_keyword = malloc(sizeof(struct keyword));
    if (new_keyword == NULL)
    {
        fprintf(stderr, "Error: cannot allocate memory for keyword\n");
        current_image->valid = 0;
        return;
    }

    // Add the new keyword to the list
    if (current_image->keywords == NULL)
    {
        current_image->keywords = new_keyword;
    }
    else
    {
        struct keyword *current_keyword = current_image->keywords;
        while (current_keyword->next != NULL)
        {
            current_keyword = current_keyword->next;
        }
        current_keyword->next = new_keyword;
    }
    current_image->num_keywords++;
    new_keyword->next = NULL;
    new_keyword->keyword = keyword;
    new_keyword->text = text;
}

// Method to free the memory
void free_everything(struct image *current_image)
{
    // Free the memory
    struct chunk *current_chunk = current_image->chunks;
    while (current_chunk != NULL)
    {
        struct chunk *next_chunk = current_chunk->next;
        free(current_chunk->type);
        free(current_chunk->data);
        free(current_chunk);
        current_chunk = next_chunk;
    }

    struct keyword *current_keyword = current_image->keywords;
    while (current_keyword != NULL)
    {
        struct keyword *next_keyword = current_keyword->next;
        free(current_keyword->keyword);
        free(current_keyword->text);
        free(current_keyword);
        current_keyword = next_keyword;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CRC32 functions from the PNG specification
// https://www.w3.org/TR/2023/CR-png-3-20230921/#samplecrc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Table of CRCs of all 8-bit messages. */
unsigned long crc_table[256];

/* Flag: has the table been computed? Initially false. */
int crc_table_computed = 0;

/* Make the table for a fast CRC. */
void make_crc_table(void)
{
    unsigned long c;
    int n, k;

    for (n = 0; n < 256; n++)
    {
        c = (unsigned long)n;
        for (k = 0; k < 8; k++)
        {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc_table[n] = c;
    }
    crc_table_computed = 1;
}

/* Update a running CRC with the bytes buf[0..len-1]--the CRC
   should be initialized to all 1's, and the transmitted value
   is the 1's complement of the final running CRC (see the
   crc() routine below). */

unsigned long update_crc(unsigned long crc, const unsigned char *buf,
                         unsigned int len)
{
    unsigned long c = crc;
    int n;

    if (!crc_table_computed)
        make_crc_table();
    for (n = 0; n < len; n++)
    {
        c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }
    return c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** CHUNK STRUCTURE
 *  After the signature we start with the chunks of data
 *  Each chunk has the following structure:
 *  4 bytes: length of the chunk
 *  4 bytes: chunk type
 *  n bytes: chunk data | Only if length > 0
 *  4 bytes: CRC32 checksum of the chunk data
 */

/** CHUNK TYPES
 * IHDR: image header (always the first chunk) | Required, Unique
 * PLTE: palette table | Optional
 * IDAT: image data | Required, Multiple
 * IEND: image trailer (always the last chunk) | Required, Unique
 *
 * tEXt: textual data | Optional
 */

/** IHDR CHUNK (13 bytes) | Required, Unique
 * 4 bytes: length (always 13)
 * 4 bytes: chunk type (0x49 0x48 0x44 0x52)
 *
 * 4 bytes: width (in pixels)
 * 4 bytes: height (in pixels)
 * 1 byte: bit depth (1, 2, 4, 8, 16)
 * 1 byte: color type (0: grayscale, 2: Truecolour (RGB), 3: indexed, 4: grayscale + alpha, 6: Truecolour (RGB) with alpha)
 * 1 byte: compression method (always 0)
 * 1 byte: filter method (always 0)
 * 1 byte: interlace method (0: no interlace, 1: Adam7 interlace)
 *
 * 4 bytes: CRC32 checksum
 */

/** PLTE CHUNK (n bytes) | Optional, Unique
 * This chunk contains the palette entries for indexed color images
 * It should appear for color type 3 (indexed color) | Required
 * It may appear for color type 2 (Truecolour (RGB)) and 6 (Truecolour (RGB) with alpha) | Optional
 * It must not appear for color type 0 (grayscale) and 4 (grayscale with alpha) | Forbidden
 *
 *
 *
 * 4 bytes: length (always a multiple of 3)
 * 4 bytes: chunk type (0x50 0x4c 0x54 0x45)
 *
 * n bytes: palette entries (3 bytes per entry from 1 to 256 entries)
 *      each entry is 3 bytes:
 *          1 byte: red
 *          1 byte: green
 *          1 byte: blue
 *
 * 4 bytes: CRC32 checksum
 */

/** tEXt CHUNK (n bytes) | Optional, Multiple
 * This chunk contains human-readable textual data
 *
 * 4 bytes: length
 * 4 bytes: chunk type (0x74 0x45 0x58 0x74)
 *
 * n bytes: keyword (1 to 79 bytes) (character string) | Describes the type of information contained in the text chunk
 * 1 byte: null separator (0x00)
 * n bytes: text string (character string) (may be empty) | Contains the actual text
 */

/** IDAT CHUNK (n bytes) | Required, Multiple
 * This chunk contains the actual image data
 * Multiple IDAT chunks may appear in a PNG file
 * They must appear consecutively with no other intervening chunks
 * The compressed datastream is the concatenation of the contents of all the IDAT chunks
 *
 * 4 bytes: length (always > 0)
 * 4 bytes: chunk type (0x49 0x44 0x41 0x54)
 * n bytes: image data (compressed)
 * 4 bytes: CRC32 checksum
 */

/** IEND CHUNK (4 bytes) | Required, Unique
 * This chunk marks the end of the PNG datastream
 * It must appear last
 *
 * 4 bytes: length (always 0)
 * 4 bytes: chunk type (0x49 0x45 0x4e 0x44)
 * 4 bytes: CRC32 checksum (0xae 0x42 0x60 0x82)
 *
 */
