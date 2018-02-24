/*
* @Author
* Student Name: Mustafa Efekan PEKEL
* Student ID : 150140050
* E-mail: pekelm@itu.edu.tr
* Date: 09/03/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	srand(time(NULL));

    printf("Enter number of players per team (N)\n");
    int N;
    scanf("%d",&N);

    printf("Enter probability for a successful pass (P)\n");
    int P;
    scanf("%d",&P);

    printf("Enter number of passes to win a single round (W)\n");
    int W;
    scanf("%d",&W);

    printf("Enter target score (S)\n");
    int S;
    scanf("%d",&S);

    int team_selected, team_unselected;
    int round = 1;
    int team1_score = 0, team2_score = 0;
    int team1_passes = 0, team2_passes = 0;

    while(team1_score != S && team2_score != S) {					    // MAIN	MATCH LOOP
            if(rand()%100 >= 50) {										// team selecting(%50)
                team_selected = 2;
                team_unselected = 1;
            }
            else {
                team_selected = 1;
                team_unselected = 2;
            }

            printf("\nRound-%d:\n",round);
            printf("\tTeam%d is selected\n",team_selected);
            int person = 1+rand()%N;
            printf("\tPlayer%d",person);

            if (team_selected == 1) {									// first player counts as a pass
                team1_passes +=1;
            }
            else{
                team2_passes +=1;
            }
            round++;

            while(team1_passes != W && team2_passes != W){				// ROUND LOOP



                if(1 + rand()%100 <= P) {									//successful pass
                    int new_person = 1+rand()%N;
                    while(person == new_person) {
                        new_person = 1+rand()%N;
                    }
                    person = new_person;
                    printf(" -> Player %d",person);
                    if (team_selected == 1) {
                        team1_passes +=1;
                    }
                    else{
                        team2_passes +=1;
                    }
                }
                else {														//unsuccessful pass
                    printf("\n\tTeam%d captured the ball!\n",team_unselected);
                    if (team_selected == 1) {
                        team1_passes = 0;
                    }
                    else{
                        team2_passes = 0;
                    }
                    int temp;
                    temp = team_selected;
                    team_selected = team_unselected;
                    team_unselected = temp;
                    person = 1+rand()%N;
                    printf("\tPlayer%d",person);
                    if (team_selected == 1) {
                        team1_passes +=1;
                    }
                    else{
                        team2_passes +=1;
                    }
                }
                if(team1_passes == W ) {									//if team1 reaches round ending pass number
                    team1_score += 1;
                    printf("\n\tSuccess! New Score of Team1 is %d", team1_score);
                    team1_passes = 0;
                    break;
             }
                else if(team2_passes == W) {								//if team2 reaches round ending pass number
                    team2_score += 1;
                    printf("\n\tSuccess! New Score of Team2 is %d", team2_score);
                    team2_passes = 0;
                    break;
             }


        }
        }

        if(team1_score == S) {										//if team1 reaches match ending goal number
            printf("\n\nGAME OVER: Team1 reached the target score (%d) and won the game.",S);
        }
        else if(team2_score == S) {									//if team2 reaches match ending goal number
            printf("\n\nGAME OVER: Team2 reached the target score (%d) and won the game.",S);
        }



        return 0;
    }






