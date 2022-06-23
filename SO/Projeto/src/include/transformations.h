#ifndef TRANSFORMATIONS_
#define TRANSFORMATIONS_

void single_transformation(char *input_file, char *output_file, char *transforms, char *transf_path);

void initial_transformation(char *input_file, int i, char *transforms, char *transf_path, int transf_pipe[]);

void middle_transformation(int i, char *transforms, char *transf_path, int transf_pipe1[], int transf_pipe2[]);

void final_transformation(char *output_file, int i, char *transforms, char *transf_path, int transf_pipe[]);

#endif