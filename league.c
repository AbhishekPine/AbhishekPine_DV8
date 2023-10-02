#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char* Club;
    int Matches_Played;
    int Wins;
    int Draws;
    int Losses;
    int Points;
    int GF;
    int GA;
    int GD;
} 
League_Table_Attributes;

typedef struct 
{
    int week;
    char* name;
    char** players;
    char** teams;
    char** team_names;
    char*** schedule;
    League_Table_Attributes* standings;
} 
League;

void set_teams(League* league);
void set_players(League* league);
char*** create_balanced_round_robin(char** teams, int team_count);
League* init_league(char* option);
League_Table_Attributes* init_league_table();
void print_schedule(char*** schedule, int team_count);

int main() 
{
    League* league = init_league("option");
    print_schedule(league->schedule, sizeof(league->team_names) / sizeof(league->team_names[0]));
    return 0;
}

void set_teams(League* league) 
{
    for (int i = 0; i < sizeof(league->team_names) / sizeof(league->team_names[0]); i++) {
        char* name = league->team_names[i];
        char** team = malloc(sizeof(char*));
        *team = malloc(strlen(name) + 1);
        strcpy(*team, name);
        league->teams[i] = *team;
    }
}

void set_players(League* league) 
{
    for (int i = 0; i < sizeof(league->teams) / sizeof(league->teams[0]); i++) {
        char** team = league->teams[i];
        for (int j = 0; j < sizeof(team->players) / sizeof(team->players[0]); j++) {
            char* player = team->players[j];
            league->players[i] = player;
        }
    }
}

char*** create_balanced_round_robin(char** teams, int team_count) 
{
    char*** schedule = malloc((team_count - 1) * sizeof(char**));
    if (team_count % 2 == 1) {
        teams = realloc(teams, (team_count + 1) * sizeof(char*));
        teams[team_count] = NULL;
    }
    int mid = team_count / 2;
    for (int i = 0; i < team_count - 1; i++) {
        char** first_half = malloc(mid * sizeof(char*));
        char** second_half = malloc(mid * sizeof(char*));
        for (int j = 0; j < mid; j++) {
            first_half[j] = teams[j];
            second_half[j] = teams[mid + j];
        }
        second_half = realloc(second_half, mid * sizeof(char*));
        for (int j = 0; j < mid; j++) {
            char* temp = second_half[j];
            second_half[j] = second_half[mid - j - 1];
            second_half[mid - j - 1] = temp;
        }
        schedule[i] = malloc(2 * mid * sizeof(char*));
        for (int j = 0; j < mid; j++) {
            schedule[i][j] = first_half[j];
            schedule[i][mid + j] = second_half[j];
        }
    }
    return schedule;
}

League* init_league(char* option) 
{
    League* league = malloc(sizeof(League));
    league->week = 0;
    league->name = "name";
    league->players = malloc(sizeof(char*));
    league->teams = malloc(sizeof(char*));
    league->team_names = malloc(sizeof(char*));
    league->team_names[0] = "team1";
    league->team_names[1] = "team2";
    set_teams(league);
    set_players(league);
    league->schedule = create_balanced_round_robin(league->team_names, sizeof(league->team_names) / sizeof(league->team_names[0]));
    league->standings = init_league_table();
    return league;
}

League_Table_Attributes* init_league_table() 
{
    League_Table_Attributes* standings = malloc(sizeof(League_Table_Attributes));
    standings->Club = "Club";
    standings->Matches_Played = 0;
    standings->Wins = 0;
    standings->Draws = 0;
    standings->Losses = 0;
    standings->Points = 0;
    standings->GF = 0;
    standings->GA = 0;
    standings->GD = 0;
    return standings;
}

void print_schedule(char*** schedule, int team_count) 
{
    for (int i = 0; i < team_count - 1; i++) {
        printf("Week %d:\n", i + 1);
        for (int j = 0; j < team_count / 2; j++) {
            printf("%s vs %s\n", schedule[i][j], schedule[i][team_count / 2 + j]);
        }
        printf("\n");
    }
}