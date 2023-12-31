#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // we loop over candidate_count that is initilalized above (argc -1 becuase of the run command of the program)
    // for each candiate, we check if the candiate name input into this function can be found inside argv (actual candidates)
    // loop over candidates struct (.name) and see if candiate's name exists.
    // if candiate's name matches candidates, return true.
    // if candiate's name does not match candidates, return false.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false; // Return false after checking all candidates and none found.
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // loop over all candidates and find highest vote between them all
    // print the winner with the most votes.
    int most_votes = 0;

    // loop through each candidates vote and update the current leader
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > most_votes)
        {
            most_votes = candidates[i].votes;
        }
    }

    // loop through candidates and find the candidate with matching votes to most_votes, this is the winner we print.
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == most_votes)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}