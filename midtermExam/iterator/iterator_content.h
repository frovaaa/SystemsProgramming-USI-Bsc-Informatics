struct iterator;

struct sequence {
    const char * begin;
    const char * end;
};

struct iterator * create_iterator();
void destroy_iterator(struct iterator *);
int set_text(struct iterator *, const struct sequence *);
int set_separators(struct iterator *, const struct sequence *);
int get_next(struct iterator *, struct sequence *);
