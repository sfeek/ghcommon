#include "ghcommon.h"

int main (void)
{
	int error = SUCCESS;
	char *s1 = NULL;
	char *s2 = NULL;
	char *s3 = NULL;
	char* s4 = NULL;

	
	size_t count = get_string (&s1,"\nEnter a string: ");
	size_t sl = len_string(&s1);

	printf ("\nThe string had %zu characters according to get_string and %zu according to len_string. The string was: %s\n",count,sl,s1);
		
	if (copy_string (&s3, " We are taking out all spaces    from this sentence! "))
	{
		printf ("Copy error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (replace_string (&s3, " ", ""))
	{
		printf ("Replace error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("%s\n", s3);

	if (copy_string (&s1, "This is a"))
	{
		printf ("Copy error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (copy_string (&s2, " Here is another sentence for the end."))
	{
		printf ("Copy error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (append_string (&s1, " test of my program!"))
	{
		printf ("Concat error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (append_string (&s1, " I hope that it works fine this way."))
	{
		printf ("Concat error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (append_string (&s1, s2))
	{
		printf ("Concat error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (replace_string (&s1, "fine", "abcdefghijklmnopqrstuvwyz"))
	{
		printf ("Replace error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("The concat string: %s\n", s1);

	if (wrap_string (&s1, 40))
	{
		printf ("Wrap error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("\n\n%s\n", s1);

	if (sprintf_string (&s1, "%s", "This is sprintf!"))
	{
		printf ("Sprintf error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("\n%s", s1);

	copy_string(&s4, s1);

	if (sub_string(&s4, 5, 6))
	{
		printf("Sub_string error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf("\nThe substring of %s from 5 to 6 is: %s\n", s1,s4);

	copy_string(&s4, s1);

	if (left_string(&s4, 5))
	{
		printf("Right_string error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf("\nThe left string of %s from 0 to 5 is: %s\n", s1, s4);

	copy_string(&s4, s1);

	if (right_string(&s4, 5))
	{
		printf("Left_string error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf("\nThe right string of %s from 0 to 5 is: %s\n", s1, s4);

	if (truncate_string (&s1, 3))
	{
		printf ("Right_string error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("\nThe truncated at 3 string: %s\n", s1);

main_cleanup:
	if (s1) free (s1);
	if (s2) free (s2);
	if (s3) free (s3);
	if (s4) free (s4);

	
	pause_for_enter("\nPress Enter to Exit!\n");
	return error;
}

