#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // if name matches candidate, update global perf with name and rank.
    for (int i = 0; i < candidate_count; i++)
    {
        // if successfull and name and rank is correct, return true.
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    // otherwise we return false.
    return false;
}

// Tabulate votes for non-eliminated candidates
// update numbers of votes on each candidate
// loop over x amount of voters (voter_count) and create 1 table per voter for each vote. preferences[i][0]/preferences[i][1] and
// preferences[i][3] for example. check if eliminated is true or false, if we hit an eliminated vote we use break;
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break; // break out to continue.
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // If any candidate has more than half of the vote, their name should be printed and the function should return true.
    // If nobody has won the election yet, the function should return false.

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // loop through candidates. if candidate is not eliminated and votes are lower than the min (voter_count), the value of min
    // becomes candidate.votes.
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // takes in min from find_min() which has the minimum of votes in the election
    int countNotEliminated = 0;
    int trackMinVotes = 0;

    // loops through every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate.eliminated == false, add 1 to countNotEliminated
        if (!candidates[i].eliminated)
        {
            countNotEliminated++;
        }
        // if candidates.votes == min (its a tie if all candidates have an equal score, ergo everyone has the same amount of votes
        // as min value)
        if (candidates[i].votes == min)
        {
            trackMinVotes++;
        }
    }
    // if we have the same amount of non eliminated candidates as we do with candidates with min votes, we have a tie. they are all
    // equal, nobody is in thw lead.
    if (countNotEliminated == trackMinVotes)
    {
        // if true, we have a tie and return true
        return true;
    }
    // if none above, we return false as it is not a tie. if one of the variables countNotEliminated or trackMinVotes is greater
    // than the other, we have a winner/revote not a tie.
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // loop through all candidates, check if candidate has a score that matches min, if so we eliminate.
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}