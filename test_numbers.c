#include "ghcommon.h"

int main(void)
{
    char *line = NULL;
    char **parsed = NULL;
    size_t num_of_fields;
    double *buffer_d = NULL;
    int *buffer_i = NULL;
    char* numbers = NULL;
    size_t sz;


    /* Get an Int and Double from the user */
    int i = get_int("\nEnter an Int: ");
    double x = get_double("\nEnter a Double: ");

    printf("\n\nThe Int was: %d and the Double was: %f\n",i,x);

    sz = double_to_string(&numbers, x, 3);

    printf("\nThe number to 3 places is %s and is %zu in length\n", numbers, sz);

    sz = 0;

    sz = int_to_string(&numbers, i);

    printf("\nThe number is %s and is %zu in length\n", numbers, sz);
 
    /* Get some ints in an array */
    while (get_string(&line, "\nEnter Ints separated by commas: ") == 0);
    
    if (csv_parse(&parsed, line, &num_of_fields))
    {
        printf("\nString parsing failed!\n");
        return FAIL;
    }

    free(line);
    line = NULL;

    if (!(buffer_i = malloc(sizeof(int) * num_of_fields))) return FAIL_MEMORY;

    for (int i = 0; i < num_of_fields; i++)
    {
        string_to_int(parsed[i], &buffer_i[i]);
    }

    /* Make sure CSV parse strings are cleaned up*/
    cleanup_csv_strings(parsed, num_of_fields);

    /* Sort the Ints */
    array_sort_int(buffer_i, num_of_fields);

    /*Print out the Ints*/
    printf("\n\nSorted Ints: \n");

    for (int j = 0; j < num_of_fields; j++)
    {
        printf("%d\n", buffer_i[j]);
    }

    /* Free the buffer */
    if (buffer_i) free (buffer_i);


    /* Get some Doubles from the user */
    while (get_string(&line,"\nEnter Doubles separated by commas: ") == 0);

    if (csv_parse(&parsed, line, &num_of_fields))
    {
        printf("String parsing failed!\n");
        return FAIL;
    }

    free(line);
    line = NULL;

    if (!(buffer_d = malloc(sizeof(double) * num_of_fields))) return FAIL_MEMORY;

    for (int i = 0; i < num_of_fields; i++)
    {
        string_to_double(parsed[i], &buffer_d[i]);
    }

    cleanup_csv_strings(parsed, num_of_fields);

    array_sort_double(buffer_d, num_of_fields);

    printf("\n\nSorted Doubles: \n");

    for (int j = 0; j < num_of_fields; j++)
    {
        printf("%f\n", buffer_d[j]);
    }

    if (buffer_d) free(buffer_d);

    return SUCCESS;
}

