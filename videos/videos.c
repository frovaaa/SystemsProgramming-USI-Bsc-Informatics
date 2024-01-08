#include "videos.h"
#include "stdlib.h"
#include "string.h"

struct video
{
    unsigned id;
    char title[101];
    unsigned minutes;
    unsigned view_minutes;
    unsigned n_full_views;
    struct video *next;
};

struct platform
{
    struct video *videos;
    unsigned len;
};

struct platform *create()
{
    struct platform *p = malloc(sizeof(struct platform));
    if (p)
    {
        p->videos = 0;
        p->len = 0;
    }
    return p;
}

void destroy(struct platform *p)
{
    if (!p)
        return;

    clear(p);
    free(p);
}

void clear(struct platform *p)
{
    if (!p)
        return;

    for (struct video *videos = p->videos; videos != 0; videos = p->videos)
    {
        p->videos = videos->next;
        free(videos);
    }
    p->len = 0;
}

int add_video(struct platform *p, const char *title, int minutes)
{
    if (!p)
        return -1;

    struct video *new = malloc(sizeof(struct video));
    if (!new)
        return -1;

    new->id = p->len + 1;
    p->len += 1;
    strncpy(new->title, title, 100);
    new->title[99] = 0;
    new->minutes = minutes;
    new->n_full_views = 0;
    new->view_minutes = 0;
    new->next = p->videos;
    p->videos = new;

    return p->len;
}

int add_view(struct platform *p, int video_id, int minutes)
{
    if (!p)
        return 0;
    struct video *videos = p->videos;

    while (videos)
    {
        if (videos->id == video_id)
            break;
        videos = videos->next;
    }

    // Video not found
    if (!videos)
        return 0;

    videos->view_minutes += minutes;

    if (minutes >= videos->minutes)
        videos->n_full_views += 1;

    p->videos = videos;

    return 1;
}

int total_view_minutes(struct platform *p)
{
    if (!p)
        return 0;

    struct video *videos = p->videos;

    unsigned total_time = 0;
    while (videos)
    {
        total_time += videos->view_minutes;
        videos = videos->next;
    }

    return total_time;
}
int total_full_views(struct platform *p)
{
    if (!p)
        return 0;

    struct video *videos = p->videos;

    unsigned total_full_views = 0;
    while (videos)
    {
        total_full_views += videos->n_full_views;
        videos = videos->next;
    }

    return total_full_views;
}

int video_by_title(struct platform *p, const char *title)
{
    if (!p)
        return -1;

    struct video *videos = p->videos;

    while (videos)
    {
        if (strcmp(title, videos->title) == 0)
            break;
        videos = videos->next;
    }

    if (!videos)
        return -1;

    return videos->id;
}