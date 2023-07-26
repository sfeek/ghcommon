#include "ghcommon.h"

int append_string(char **s1, char *s2)
{
	char *t;
	int len_s1, len_s2;

	/* Make sure there is something to append */
	if (s2 == NULL)
		return SUCCESS;

	if ((len_s2 = strlen(s2)) == 0)
		return SUCCESS;

	/* Make space for expanded string */
	if (*s1 == NULL)
	{
		len_s1 = 0;
		*s1 = calloc(len_s1 + len_s2 + 1, sizeof(char));
		if (*s1 == NULL)
			return FAIL_MEMORY;
	}
	else
	{
		len_s1 = strlen(*s1);
		t = realloc(*s1, len_s1 + len_s2 + 1);

		if (t == NULL)
		{
			free(*s1);
			return FAIL_MEMORY;
		}
		else
			*s1 = t;
	}

	/* Append */
	strcat(*s1, s2);

	return SUCCESS;
}

int len_string(char **s)
{
	/* Return length */
	return strlen(*s);
}

int get_string(char **s, const char *display)
{
	char c;
	char cs[1];
	int count = 0;

	/* Show prompt text */
	printf("%s", display);

	/* Get characters from the keyboard one at a time */
	while ((c = fgetc(stdin)) != '\n')
	{
		cs[0] = c;
		cs[1] = 0;
		if (append_string(s, cs))
			break;

		count++;
	}

	/* Return number of characters that were input*/
	return count;
}

int copy_string(char **s, char *s1)
{
	char *t;
	int len;

	/* Make sure there is something to copy */
	if (s1 == NULL)
		return SUCCESS;

	if (strlen(s1) == 0)
		return SUCCESS;

	len = strlen(s1);

	/* Make space */
	if (*s == NULL)
	{
		*s = calloc(len + 1, sizeof(char));
		if (*s == NULL)
			return FAIL_MEMORY;
	}
	else
	{
		t = realloc(*s, len + 1);

		if (t == NULL)
		{
			free(*s);
			return FAIL_MEMORY;
		}
		else
			*s = t;
	}

	/* Copy */
	strcpy(*s, s1);

	return SUCCESS;
}

int truncate_string(char **s, int len)
{
	char *t;

	/* Make space */
	if (*s != NULL)
	{
		if (len >= strlen(*s))
			return FAIL; /* If truncation is larger than string length, quit */

		t = realloc(*s, len + 1);

		if (t == NULL)
		{
			free(*s);
			return FAIL_MEMORY;
		}
		else
			*s = t;
	}

	if (*s == NULL)
		return SUCCESS;

	/* Truncate by placing 0 byte*/
	(*s)[len] = '\0';

	return SUCCESS;
}

int sprintf_string(char **s, char *fmt, ...)
{
	char *t;
	int len;
	va_list args;
	/* Process arguments */
	va_start(args, fmt);
	len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	/* Make space */
	if (*s == NULL)
	{
		*s = malloc(len + 1);
		if (*s == NULL)
			return FAIL_MEMORY;
	}
	else
	{
		t = realloc(*s, len + 1);

		if (t == NULL)
		{
			free(*s);
			return FAIL_MEMORY;
		}
		else
			*s = t;
	}

	/* Send out formatted string */
	va_start(args, fmt);
	vsprintf(*s, fmt, args);
	va_end(args);

	return SUCCESS;
}

int replace_string(char **s, const char *oldW, const char *newW)
{
	char *str;
	int i, j, l, cnt = 0;
	char *r;
	int newWlen = strlen(newW);
	int oldWlen = strlen(oldW);

	if (*s == NULL)
		return FAIL;

	str = strdup(*s);
	l = strlen(str);

	/* Count number of times we need to replace */
	for (i = 0; str[i] != '\0'; i++)
	{
		if (strstr(&str[i], oldW) == &str[i])
		{
			cnt++;
			i += oldWlen - 1;
		}
	}

	/* Make space */
	r = realloc(*s, i + cnt * (newWlen - oldWlen) + 1);

	if (r == NULL)
	{
		free(*s);
		return FAIL_MEMORY;
	}

	/* Replace the words */
	i = 0;
	j = 0;

	for (i = 0; i < l;)
	{
		if (strstr(str + i, oldW) == str + i)
		{
			if (newW[0] != '\0')
				strcpy(&r[i], newW); /* Copy only if the new string is not empty */

			j += newWlen;
			i += oldWlen;
		}
		else
			r[j++] = str[i++];
	}

	/* Terminate and cleanup */
	r[j] = '\0';
	free(str);
	*s = r;

	return SUCCESS;
}

int wrap_string(char **s, int columns)
{
	int nextspace = 0;
	int l, w;
	char *t;

	if (*s == NULL)
		return FAIL;

	l = strlen(*s);
	t = realloc(*s, l + 1); /* Make space */

	if (t == NULL)
	{
		free(*s);
		return FAIL_MEMORY;
	}

	for (w = 1; w < l; w++) /* Make nice Line Wraps to columns-ish */
	{
		if (w % columns == 0)
			nextspace = 1;

		if (t[w] == ' ')
		{
			if (nextspace == 1)
			{
				t[w] = '\n';
				nextspace = 0;
			}
		}
	}

	*s = t;

	return SUCCESS;
}

/* Wait for someone to press ENTER*/
void pause_for_enter (const char *display)
{
	char ch;

	printf("%s",display);

	while (1)
	{
		ch = fgetc (stdin);

		if (ch == '\n')
			break;
	}

	return;
}

/* Math Functions */

/* Used with FOR loops to properly handle fractional step values */
int float_less_than (double f1, double f2, double step)
{
	if (f1 > f2 + 1e-14)
		return 0;

	if ((f2 + step) - f1 > 1e-14)
		return 1;
	else
		return 0;
}

/* Make sure string is really a double */
int string_todouble (const char *str, double *v)
{
	char *ptr;
	errno = 0;
	*v = strtod (str, &ptr);

	if (errno == ERANGE)
	{
		printf ("\nNumber Overflow/Underflow Error!\n");
		return FAIL_NUMBER;
	}

	if (str == ptr)
		return FAIL_NUMBER;

	return SUCCESS;
}

/* Make sure string is really an integer */
int string_toint (const char *str, int *v)
{
	char *ptr;
	errno = 0;
	*v = (int) strtol (str, &ptr, 10);

	if (errno == ERANGE)
	{
		printf ("\nNumber Overflow/Underflow Error!\n");
		return FAIL;
	}

	if (str == ptr)
	{
		printf ("\nInvalid Number Conversion Error!\n");
		return FAIL;
	}

	return SUCCESS;
}

/* Get a double or decimal value */
double get_double (const char *display)
{
	char *buffer = NULL;
	double value;
	int rtn;

	while (1)
	{
		get_string (&buffer, display);
		rtn = string_todouble (buffer, &value);
		free (buffer);

		if (rtn == SUCCESS)
			return value;
	}
}

/* Get an integer value */
int get_int (const char *display)
{
	char *buffer = NULL;
	int value;
	int rtn;

	while (1)
	{
		get_string (&buffer, display);
		rtn = string_toint (buffer, &value);
		free (buffer);

		if (rtn == EXIT_SUCCESS)
			return value;
	}
}

/* Convert Degrees to Radians */
double deg_to_rad(double deg)
{
    return PI / 180.0 * deg;
}


/* Convert Radians to Degrees */
double rad_to_deg(double rad)
{
	return rad * 180.0 / PI;
}

/* Sort an array of doubles */
void array_sort_double(double *array, int n)
{
    int i, j;
	double temp;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

/* Sort an array of doubles */
void array_sort_int(int *array, int n)
{
    int i, j, temp;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

/* CSV Functions*/
int csv_parse (char ***Array, char *str, int *number_of_fields)
{
	char *newStr = NULL;
	char currentCharacter;
	char **strArray = NULL;
	int quote = 0;
	int csvLength = strlen (str);
	int maxFieldCount = 2; /* Start with two fields as MAX */
	int *commaPositions = NULL;
	int currentField = 0;
	int cleanStringPosition = 0;
	int i;
	int startPosition = 0;
	int fieldLength;

	/* Allocate memory for the comma position array */
	if (! (commaPositions = calloc (1, 1 + sizeof (int) * maxFieldCount)))
	{
		return FAIL_MEMORY;
	}

	/* Allocate memory for "cleaned up" string the same size as the original string to guarantee that it is big enough */
	if (! (newStr = calloc (1, 1 + sizeof (char) * csvLength)))
	{
		return FAIL_MEMORY;
	}

	/* First pass through to record the correct comma positions */
	for (i = 0; i < csvLength; i++)
	{
		/* Get a single character and skip any control or garbage characters */
		if ((currentCharacter = str[i]) < 32)
			continue;

		/* Handle quotes, escapes and commas */
		switch (currentCharacter)
		{
			/* Check for escape character not inside quotes */
			case 92:
				{
					if (quote == 0)
					{
						/* Move ahead one character */
						i++;
						/* Keep the next good character and move to the next good character position*/
						newStr[cleanStringPosition++] = str[i];
						/* Move on to the next new character */
						continue;
					}

					break;
				}

			/* Check for quote and keep track of pairs */
			case 34:
				{
					/* Toggle the pair indicator */
					quote = 1 - quote;
					/* Skip the quote */
					continue;
				}

			/* Check for comma that is NOT inside quotes */
			case 44:
				{
					if (quote == 0)
					{
						/* Check to see if we need to grow our comma position array */
						if (currentField == maxFieldCount - 1)
						{
							/* Double in size each time */
							maxFieldCount *= 2;

							/* Allocate more memory for the array*/
							if (! (commaPositions = realloc (commaPositions, sizeof (int) * maxFieldCount)))
							{
								return FAIL_MEMORY;
							}
						}

						/* Keep track of the comma positions and move to the next field*/
						commaPositions[currentField++] = cleanStringPosition;
					}
				}
		}

		/* Keep the good characters and move to the next good character position  */
		newStr[cleanStringPosition++] = currentCharacter;
	}

	/* Make sure that clean string gets NULL terminator */
	newStr[cleanStringPosition] = 0;
	/* Make sure to mark the end of the string as a "comma" position so that the last field gets included in the array and include the last field */
	commaPositions[currentField++] = cleanStringPosition;
	/* Record the Total number of fields to return to the calling function */
	*number_of_fields = currentField;
	/* Allocate an array of pointers to chars, not actually allocating any strings themselves */
	strArray = realloc (Array,sizeof (char *) * currentField );
	if (strArray == NULL)
		return FAIL_MEMORY;

	/* Copy the strings to the new string array */
	for (i = 0; i < currentField; i++)
	{
		/* Calculate length of the current field plus the Null Terminator*/
		fieldLength = commaPositions[i] - startPosition + 1;
		/* Replace the comma with a Null terminator */
		newStr[commaPositions[i]] = 0;
		/* Allocate memory for the current field */
		strArray[i] = calloc (1, sizeof (char) * fieldLength);
		if (strArray[i] == NULL)
			return FAIL_MEMORY;
		/* Copy the string into the new array */
		memcpy (strArray[i], newStr + startPosition, fieldLength);
		/* Move our start position to the next field */
		startPosition = commaPositions[i] + 1;
	}

	/* Clean up the dynamic arrays */
	if (commaPositions) (commaPositions);
	commaPositions = NULL;
	if (newStr) free (newStr);
	newStr = NULL;



	/* Return the new array back to the calling function */

	return SUCCESS;
}

/*  Clean up an array of strings
    Input:  Array of strings
            Number of strings
    Return: none
*/
void cleanup_csv_strings (char **strArray, int numberOfStrings)
{
	int i;

	/* Free the individual strings */
	for (i = 0; i < numberOfStrings; i++)
	{
		free (strArray[i]);
		strArray[i] = NULL;
	}

	/* Once the strings themselves are freed, free the actual array itself */
	free (strArray);
	strArray = NULL;
}