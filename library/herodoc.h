#ifndef HERODOC_H
#define HERODOC_H



void  redirect_input(const char *filemane);
void redirect_output(const char *filename);
void redirect_output_append(const char *filename);
void redirect_herodoc(const char *filename);
void redirector(t_parser *parser);

#endif