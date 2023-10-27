#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int flag_c, flag_i, flag_u, flag_d, flag_D;

int main(int argc, char* argv[])
{
    // uniq -c -i -u source.txt output.txt
    //                  ^argv[1]
    // suniq -c -i -u 

    int val;
    while((val = getopt(argc, argv, "ciudD")) != -1){
        switch(val)
        {
        case 'c':
            flag_c = 1;
            break;
        case 'i':
            flag_i = 1;
            break;
        case 'u':
            flag_u = 1;
            break;
        case 'd':
            flag_d = 1;
            break;
        case 'D':
            flag_D = 1;
            break;
        default:
            printf("%c, err30", val);
            return 0;
        }
    }

    argc -= optind;
    argv += optind;

    // printf("%d\n", argc);
    // printf("%s\n", argv[0]);
    // printf("%s\n", argv[1]);

    FILE* fp = fopen(argv[0], "r");
    if(fp == NULL){
        printf("err\n");
        return 0;
    }
    
    char all_line[256][256];
    for(int i=0; i<256; i++){
        for(int j=0; j<256; j++){
            all_line[i][j] = '\0';
        }
    }
    // sort fp
    int line_idx = 0;
    while(fgets(all_line[line_idx], 256, fp) != 0){
        //printf("%d\n", line_idx);
        line_idx++;
    }
    // all_line contains all line 

    // sort all_line
    for(int i=0; i<line_idx+1; i++){
        for(int j=i; j<line_idx+1; j++){
            if(strcmp(all_line[i], all_line[j]) > 0){
                char tmp[256] = "\0";
                strcpy(tmp, all_line[i]);
                strcpy(all_line[i], all_line[j]);
                strcpy(all_line[j], tmp);
            }
        }
    }
    // all_line sorted

    // print it out look look
    // for(int i=0; i<line_idx+1; i++){
    //     printf("%s", all_line[i]);
    // }

    FILE* fp3 = fopen("sorted.txt", "w");
    for(int i=0; i<line_idx+1; i++){
        fprintf(fp3, "%s", all_line[i]);
    }
    fclose(fp3);

    fp = fopen("sorted.txt", "r");
    FILE* fp2 = fopen(argv[1], "w");

    char prev_line[256] = "\0";
    char this_line[256] = "\0";
    char first_exist[256] = "\0";

    fgets(prev_line, 256, fp);
    int num_of_occ_ed = 1;

	// read input line by line
	while(fgets(this_line, 256, fp) != 0){
        char prev_cmp[256] = "\0";
        char this_cmp[256] = "\0";
        if(flag_i){
            for(int i = 0; i < strlen(prev_line); i++){
                prev_cmp[i] = tolower(prev_line[i]);
            }
            prev_cmp[strlen(prev_line)] = '\0';
            for(int i = 0; i < strlen(this_line); i++){
                this_cmp[i] = tolower(this_line[i]);
            }
            this_cmp[strlen(this_line)] = '\0';
        }
        else{
            strcpy(prev_cmp, prev_line);
            strcpy(this_cmp, this_line);
        }

		if(strcmp(prev_cmp, this_cmp) != 0){
            // printf("%s %s", prev_cmp, prev_line);
            // printf("%s %s\n", this_cmp, this_line);
			// output prev
            if(!flag_d && !flag_D){
                if(!flag_u || num_of_occ_ed == 1){
                    if(flag_c == 1){
                        fprintf(fp2, "%4d %s", num_of_occ_ed, prev_line);
                    }
                    else{
                        fprintf(fp2, "%s", prev_line);
                        //printf("%s", prev_line);
                    }
                }
            }
            if(flag_D && num_of_occ_ed > 1){
                if(!flag_u || num_of_occ_ed == 1){
                    if(flag_c == 1){
                        fprintf(fp2, "%4d %s", num_of_occ_ed, prev_line);
                    }
                    else{
                        fprintf(fp2, "%s", prev_line);
                    }
                }
            }
            if(flag_c && flag_d && num_of_occ_ed > 1){
                fprintf(fp2, "%4d %s", num_of_occ_ed, first_exist);
            }
            
			num_of_occ_ed = 1;
			strcpy(prev_line, this_line); // prev line not update if not same
		}
		else{
            if(!flag_c && flag_d && num_of_occ_ed == 1){ // print first one
                if(!flag_u || num_of_occ_ed == 1){
                    if(flag_c == 1){
                        fprintf(fp2, "%4d %s", num_of_occ_ed, prev_line);
                    }
                    else{
                        fprintf(fp2, "%s", prev_line);
                    }
                }
            }
            if(flag_c && flag_d && num_of_occ_ed == 1){ // remember first one
                strcpy(first_exist, prev_line);
            }
            if(flag_D){ // print and update 
                if(!flag_u || num_of_occ_ed == 1){
                    if(flag_c == 1){
                        fprintf(fp2, "%4d %s", num_of_occ_ed, prev_line);
                    }
                    else{
                        fprintf(fp2, "%s", prev_line);
                    }
                }
                strcpy(prev_line, this_line);
            }
			num_of_occ_ed++;
		}
	}

    // output last prev

    if(!flag_d && !flag_D){
        if(!flag_u || num_of_occ_ed == 1){
            if(flag_c == 1){
                fprintf(fp2, "%4d %s", num_of_occ_ed, prev_line);
            }
            else{
                fprintf(fp2, "%s", prev_line);
            }
        }
    }
    if(flag_D && num_of_occ_ed > 1){
        if(!flag_u || num_of_occ_ed == 1){
            if(flag_c == 1){
                fprintf(fp2, "%4d %s", num_of_occ_ed, prev_line);
            }
            else{
                fprintf(fp2, "%s", prev_line);
            }
        }
    }
    if(flag_c && flag_d && num_of_occ_ed > 1){
        fprintf(fp2, "%4d %s", num_of_occ_ed, first_exist);
    }
    
    fclose(fp);
    fclose(fp2);

    return 0;
}
