#include "ghcommon.h"

int main(void)
{
    char *line = NULL;
    char **parsed = NULL;
    int num_of_fields;
    double *buffer_d = NULL;
    int *buffer_i = NULL;


    /* Get an Int and Double from the user
    int i = get_int("\nEnter an Int: ");
    double x = get_double("\nEnter a Double: ");

    printf("\n\nThe Int was: %d and the Double was: %f\n",i,x);
    */

    /* Get some ints in an array */
    get_string(&line,"\nEnter Ints separated by commas: ");

    if (csv_parse(parsed,line, &num_of_fields))
    {
        printf("String parsing failed!\n");
        return FAIL;
    }

    free(line);
    line = NULL;

    buffer_i = malloc(sizeof(int) * num_of_fields);

    if (buffer_i == NULL)
        return FAIL;

    for (int i = 0; i < num_of_fields; i++)
    {
        string_toint(parsed[i], &buffer_i[i]);
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
    if (buffer_i) free(buffer_i);

    /*
    /* Get some Doubles from the user 
    get_string(&line,"\nEnter Doubles separated by commas: ");

    if (!(parsed = csv_parse(line, &num_of_fields)))
    {
        printf("String parsing failed!\n");
        return 1;
    }

    free(line);
    line = NULL;

    buffer_d = realloc(buffer_d, sizeof(double) * num_of_fields);

    if (buffer_d == NULL)
        return 1;

    for (int i = 0; i < num_of_fields; i++)
    {
        string_todouble(parsed[i], &buffer_d[i]);
    }

    cleanup_csv_strings(parsed, num_of_fields);

    array_sort_double(buffer_d, num_of_fields);

    printf("\n\nSorted Doubles: \n");

    for (int j = 0; j < num_of_fields; j++)
    {
        printf("%f\n", buffer_d[j]);
    }

    if (buffer_d) free(buffer_d);
    */
    return SUCCESS;
}

