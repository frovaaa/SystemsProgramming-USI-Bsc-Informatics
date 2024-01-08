#ifndef TFORMAT_H_INCLUDED
#define TFORMAT_H_INCLUDED

struct t_opts {
    int format_paragraphs;
    int format_punctuation;
    int max_line_len;
};

extern void t_format (char * t, const struct t_opts * opt);
#endif
