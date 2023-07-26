#include "ghcommon.h"

int main (void)
{
	int error = SUCCESS;
	char *s1 = NULL;
	char *s2 = NULL;
	char *s3 = NULL;

	
	int count = get_string (&s1,"\nEnter a string: ");
	int sl = len_string(&s1);

	printf ("\nThe string had %d characters according to string_get and %d according to string_len. The string was: %s\n",count,sl,s1);
		
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

	if (truncate_string (&s1, 5))
	{
		printf ("Truncate error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("\nThe truncated string: %s\n", s1);

main_cleanup:
	free (s1);
	free (s2);
	free (s3);

	pause_for_enter("\nPress Enter to Exit!\n");
	return error;
}

