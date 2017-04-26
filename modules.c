#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void hlink_removal(FILE * fp)
{
	//FILE * fp;
	//get file length to create buffer to read it.
	int file_length;
	char char_reader;
	int j = 0;
	//fp = fopen(filename, "r+");
	fseek(fp, 0L, SEEK_END);
	file_length = ftell(fp);
	rewind(fp);
	
	char * buf[file_length];

	//put the file in the buffer
	fread(buf, sizeof(char), file_length, fp);

	//find hyperlinks in the code and replace it with nothing
	for(int i = 0; i < file_length; i++)
	{
		j = i;
		if(buf[i]=="a" && buf[i+2]=="h" && buf[i+3]=="r" && buf[i+4]=="e")
		{
			buf[j-1]="";
			do
			{
				buf[j]="";
				j++;
			}
			while(buf[j] != ">");

			if(buf[j] != "<")
				j++;
			else if(buf[j]=="<" && buf[j+1]=="/" && buf[j+2]=="a" && buf[j+3]==">")
			{
				buf[j] = "";
				buf[j+1] = "";
				buf[j+2] = "";
				buf[j+3] = "";
			}

			i = j;

		}
	}

	while(fp)
		fwrite(buf, 1, sizeof(buf), fp);

}

// void ad_removal(char * filename)
// {
// 	FILE * fp;
// 	//get file length to create buffer to read it.
// 	int file_length;
// 	char char_reader;
// 	int j = 0;
// 	fp = fopen(filename, "r+");
// 	fseek(fp, 0L, SEEK_END);
// 	file_length = ftell(fp);
// 	rewind(fp);
	
// 	char buf[file_length];

// 	//put the file in the buffer
// 	fgets(buf, file_length, fp);
// }


void ad_removal(FILE * fp)
{
/*
    // getting the size of our ad list file
    FILE * adptr = fopen("adlist.txt", "r");
    fseek(adptr, 0L, SEEK_END);
    int ad_length = ftell(adptr);
    char ad_buf[ad_length];
    rewind(adptr);
       
    //getting ad file into the buffer
    fread(ad_buf, sizeof(char), adptr);
*/
    //*************keeping the above thing optional for now**************//
      
    //getting the file length of HTML file for buffer size
    int file_length;
    fseek(fp, 0L, SEEK_END);
    file_length = ftell(fp);
    char * page_buf[file_length];       
    rewind(fp);
    int i=0, j=0, k=0;    
    //reading the file into the buffer
    fread(page_buf, sizeof(char), file_length, fp); //reading done
       
    //we have stored the list of major advertisement domains which will be accessed at the time of page displaying, if the user wishes so and the module will compare. 
       
    //hardcoding a list of common words that may occur in the names of ad domains
    char * ad_strings[] = {"ad", "banner", "a.", "affilia", "amaz", "auto", "audit", "bans", "blog", "blue", "bri", "buzz", "cash", "casino", "click", "clk", "conte", "count", "creat", "direct", "domain", "e-", "euro", "ex", "eye", "fast", "fin", "free", "fl", "game", "gl", "go", "hit", "im", "inf", "inte", "ind", "ins", "ip", "it", "ju", "lig", "link", "mad", "mar", "med", "my", "neds", "net", "new", "oas", "one", "ope", "page", "pay", "pee", "per", "pix", "play", "pop", "porn", "pr", "pro", "pub", "qu", "rad", "rank", "rea", "red", "rek", "rev", "ro", "se", "sex", "serv", "share", "shiny", "si", "sp", "stat", "su", "target", "text", "the", "top", "track", "trad", "traffic", "val", "vi", "web", "wi", "xxx", "yield", "ze"};//92 elements

	char * href_begin[] = "<a href=\"";
	char * href_end[] = "</a>";

	// snippet for comparing..........this might require some changes 
	while(i<file_length)
	{
		if(href_begin[j]==page_buf[i])
    	{
    		j++;
    		i++;
    	}
    	if(j == strlen(find_head)) //i is already at next place now
    	{
    		while(href_end[k] != pagebuf[i])
    		{
    				page_buf[i] = "";
    				k++;
    				i++;
    		}
    	}
	    
	}

}

void page_layout(FILE * fp)
{
	//this fn includes the line <link rel="stylesheet" type="text/css" href="..."> between the <head></head> tags
	//to apply the css file to HTML file

	int file_length;
    fseek(fp, 0L, SEEK_END);
    file_length = ftell(fp);
    char * page_buf[file_length];
	rewind(fp);
	char * to_insert="<link rel=\"stylesheet\" type=\"text/css\" href=\"Style(main).css\">"
    
    int i=0, j=0, k=0;    

    //reading the file into the buffer
    fread(page_buf, sizeof(char), file_length, fp); //reading done

    //now to find <head> and put css in it and write the file

    char * find_head[] = "<head>";

    while(i < file_length)
    {
    	if(find_head[j]==page_buf[i])
    	{
    		j++;
    		i++;
    	}
    	if(j == strlen(find_head)) //i is already at next place now
    	{
	    	fseek(fp, i, SEEK_SET);
    		finsert(fp, to_insert);

    	}
    }

}

// void captcha_handle(FILE * fp)
// {

// }