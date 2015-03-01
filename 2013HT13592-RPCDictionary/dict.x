struct dictTuple
{
     char word[50];
     char meaning[50];
};

program DICTIONARY
{
	version INSERT_LOOKUP_VERS
	{
		int INSERT_LOOKUP(dictTuple) = 1;
	} = 1;
} = 0x01313592;
		
