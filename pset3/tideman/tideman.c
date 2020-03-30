#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
// ^ num. of distinct pairs n(n-1) / 2


int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // Clear preferences matrix
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i += 1)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Storing rank count separately for clarity
    int ranks_count = candidate_count;
    // Current ranked candidate vs. 'loser' candidate
    int selected_candidate, other_candidate;

    for (int i = 0; i < ranks_count; i += 1)
    {
        selected_candidate = ranks[i];
        for (int j = i + 1; j < candidate_count; j += 1)
        {
            other_candidate = ranks[j];
            preferences[selected_candidate][other_candidate] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int num_pairs = 0;
    for (int i = 0; i < candidate_count; i += 1)
    {
        for (int j = 0; j < candidate_count; j += 1)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[num_pairs].winner = i;
                pairs[num_pairs].loser = j;
                num_pairs += 1;
            }
        }
    }
    pair_count = num_pairs;
    return;
}

// Merge two sorted half-arrays
void merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    // Temp arrays
    pair L[n1], R[n2];
    for (i = 0; i < n1; i++)
    {
        L[i].winner = pairs[l + i].winner;
        L[i].loser = pairs[l + i].loser;
    }
    for (j = 0; j < n2; j++)
    {
        R[j].winner = pairs[m + 1 + j].winner;
        R[j].loser = pairs[m + 1 + j].loser;
    }

    // Merge into original array
    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (preferences[L[i].winner][L[i].loser] >= preferences[R[j].winner][R[j].loser])
        {
            pairs[k].winner = L[i].winner;
            pairs[k].loser = L[i].loser;
            i++;
        }
        else
        {
            pairs[k].winner = R[j].winner;
            pairs[k].loser = R[j].loser;
            j++;
        }
        k++;
    }

    // Copy remaining pairs
    while (i < n1)
    {
        pairs[k].winner = L[i].winner;
        pairs[k].loser = L[i].loser;
        i++;
        k++;
    }
    while (j < n2)
    {
        pairs[k].winner = R[j].winner;
        pairs[k].loser = R[j].loser;
        j++;
        k++;
    }
}

// Merge sort
void merge_sort(int l, int r)
{
    if (r > l)
    {
        // Avoids overflow for large l and h (instead of (l + r) / 2)
        int m = l + (r - l) / 2;
        merge_sort(l, m);
        merge_sort(m + 1, r);
        merge(l, m, r);
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_sort(0, pair_count);
    return;
}

// Check if graph is cyclic or not
bool is_cyclic(int winner, int loser, int first_winner, bool visited[])
{
    // base condition
    if (loser == first_winner)
    {
        return true;
    }

    // check if already visited
    for (int i = 0; i < candidate_count; i += 1)
    {
        if (visited[i] && i == loser)
        {
            return false;
        }
    }

    // check for cycles
    for (int i = 0; i < candidate_count; i += 1)
    {
        if (locked[loser][i] && is_cyclic(loser, i, first_winner, visited))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i += 1)
    {
        // To store candidate index (visited vertex)
        bool visited_vertices[candidate_count];
        int first_winner = pairs[i].winner;

        // Mark all vertices as not visited
        for (int j = 0; j < candidate_count; j += 1)
        {
            visited_vertices[j] = false;
        }

        // Check if locked graph is acyclic and add edge
        if (!is_cyclic(pairs[i].winner, pairs[i].loser, first_winner, visited_vertices))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int eliminated_candidates[candidate_count];
    int k = 0, elim_length; // keep track of ^ index

    for (int i = 0; i < candidate_count; i += 1)
    {
        for (int j = 0; j < candidate_count; j += 1)
        {
            if (i == j)
            {
                continue;
            }
            if (locked[i][j])
            {
                eliminated_candidates[k] = j;
                k += 1;
            }
        }
    }

    elim_length = k;
    int winner = 0;
    bool eliminated;

    for (int i = 0; i < candidate_count; i += 1)
    {
        eliminated = false;
        for (k = 0; k < elim_length; k += 1)
        {
            if (eliminated_candidates[k] == i)
            {
                eliminated = true;
                break;
            }
        }

        if (!eliminated)
        {
            winner = i;
            break;
        }
    }

    printf("%s", candidates[winner]);
    printf("\n");
    return;
}

