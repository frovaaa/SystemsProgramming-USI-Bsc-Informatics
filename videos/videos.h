#ifndef VIDEOS_H_INCLUDED
#define VIDEOS_H_INCLUDED

struct platform;

struct platform * create ();    
void destroy (struct platform * p);    
void clear (struct platform * p);    

int add_video (struct platform * p, const char * title, int minutes);
int add_view (struct platform * p, int video_id, int minutes);

int total_view_minutes (struct platform * p);
int total_full_views (struct platform * p);

int video_by_title (struct platform * p, const char * title);

#endif
