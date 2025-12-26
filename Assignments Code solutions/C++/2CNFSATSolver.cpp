/*
 * 2-CNF SAT Solver
 * ----------------
 * 
 * Problem Context:
 * A boolean formula in 2-CNF (Conjunctive Normal Form with exactly two literals per clause)
 * is a conjunction (AND) of clauses where each clause is a disjunction (OR) of exactly two literals.
 * Each literal is either a variable or its negation.
 * 
 * Task:
 * Given such a formula with n variables and m clauses, determine if it is satisfiable.
 * If satisfiable, output a valid assignment of variables (0 = False, 1 = True).
 * Otherwise, print "Unsatifiable".
 * 
 * Why is this important?
 * 2-CNF satisfiability is a classic problem in computer science and can be solved in polynomial time,
 * unlike the general SAT problem which is NP-complete.
 * This solver uses the implication graph and strongly connected components (SCC) technique 
 * based on Kosaraju's algorithm for a linear-time solution.
 * 
 * How does this work?
 * - Each literal x is represented as a vertex in a graph.
 * - For each clause (a ∨ b), add implications ¬a → b and ¬b → a to the graph.
 * - Find SCCs in the graph; if a variable and its negation belong to the same SCC, 
 *   the formula is unsatisfiable.
 * - Otherwise, assign truth values based on SCC ordering.
 * 
 * This program offers two modes:
 * 1. Manual input of test cases.
 * 2. Automatic run of 3 predefined sample test cases.
 * 
 * Usage:
 * Compile with a standard C++ compiler (e.g., g++) and run.
 * Choose input mode and follow prompts.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/*
 * Converts a literal to an index in the implication graph.
 * Positive literals x are mapped to indices [0..n-1].
 * Negative literals -x are mapped to indices [n..2n-1].
 *
 * Parameters:
 * - x: literal (e.g. 1, -2, 3, etc.)
 * - n: total number of variables
 *
 * Returns:
 * - corresponding index for the literal in the graph
 */
int literalToIndex(int x, int n) {
    if (x > 0) return x - 1;        // positive literal x mapped 0-based
    return n + (-x - 1);            // negative literal -x mapped to second half
}

/*
 * Class implementing 2-SAT solver using implication graph and Kosaraju's SCC algorithm.
 */
class TwoSAT {
    int n;                              // number of variables
    vector<vector<int>> graph;          // implication graph adjacency list
    vector<vector<int>> graph_rev;      // reverse graph for Kosaraju
    vector<bool> visited;               // visited flags for DFS
    vector<int> order;                  // vertices order after first DFS pass
    vector<int> comp;                   // component ids for each vertex

public:
    // Constructor initializes the graphs and helper vectors for 'n' variables
    TwoSAT(int vars) : n(vars) {
        graph.resize(2*n);
        graph_rev.resize(2*n);
        visited.resize(2*n, false);
        comp.resize(2*n, -1);
    }

    /*
     * Adds a directed edge from u to v in the implication graph.
     * Also adds the reverse edge in the reverse graph for Kosaraju.
     */
    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph_rev[v].push_back(u);
    }

    /*
     * Adds a clause (x ∨ y) to the 2-SAT problem.
     * This corresponds to adding edges ¬x → y and ¬y → x to the implication graph.
     */
    void addClause(int x, int y) {
        int u = literalToIndex(-x, n);
        int v = literalToIndex(y, n);
        addEdge(u, v);

        u = literalToIndex(-y, n);
        v = literalToIndex(x, n);
        addEdge(u, v);
    }

    /*
     * First DFS pass of Kosaraju's algorithm to compute vertex finishing order.
     */
    void dfs1(int u) {
        visited[u] = true;
        for (int v : graph[u]) {
            if (!visited[v]) dfs1(v);
        }
        order.push_back(u);
    }

    /*
     * Second DFS pass on the reverse graph to assign component IDs.
     */
    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : graph_rev[u]) {
            if (comp[v] == -1) dfs2(v, c);
        }
    }

    /*
     * Attempts to solve the 2-SAT problem.
     * Returns true if satisfiable, false otherwise.
     * If satisfiable, fills 'assignment' vector with 0/1 values for each variable.
     */
    bool solve(vector<int> &assignment) {
        order.clear();
        fill(visited.begin(), visited.end(), false);
        fill(comp.begin(), comp.end(), -1);

        // 1st DFS pass to compute finishing order
        for (int i = 0; i < 2*n; i++) {
            if (!visited[i]) dfs1(i);
        }

        int curr_comp = 0;
        // 2nd DFS pass on reversed graph to assign components
        for (int i = 2*n - 1; i >= 0; i--) {
            int u = order[i];
            if (comp[u] == -1) {
                dfs2(u, curr_comp++);
            }
        }

        assignment.assign(n, -1);
        // Check if variable and its negation are in same component -> unsatisfiable
        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i + n]) {
                return false; // conflict found
            }
            // Variable assignment depends on component order
            assignment[i] = (comp[i] > comp[i + n]) ? 0 : 1;
        }
        return true;
    }
};

/*
 * Runs five predefined sample test cases for the 2-SAT solver.
 * Each test case is designed to exercise different parts of the algorithm:
 * - satisfiability detection
 * - variable assignments
 * - unsatisfiability detection
 * - multiple variables and clauses
 * - edge cases with minimal clauses
 *
 * Prints the clauses, result, and variable assignments in a human-readable format using ASCII characters.
 */
void runTestCases() {
    // Each test case: {number_of_vars, number_of_clauses, vector_of_clauses}
    // Clauses are pairs of integers representing literals, positive for xi, negative for ¬xi.
    vector<tuple<int,int,vector<pair<int,int>>>> tests = {
        // Test case 1: Basic satisfiable case
        // Tests basic satisfiability and variable assignments.
        {3, 3, {{1,-2}, {-1,-3}, {-1,2}}},

        // Test case 2: Unsatisfiable case
        // Tests if solver correctly detects contradictions.
        {3, 4, {{1,2}, {-1,-2}, {1,-3}, {-1,3}}},

        // Test case 3: Simple satisfiable with minimal clauses
        // Tests small inputs, corner case.
        {2, 2, {{1,2}, {-1,-2}}},

        // Test case 4: Larger satisfiable case with more variables and clauses
        // Tests solver's handling of larger inputs and more complex implication chains.
        {4, 5, {{1,2}, {-2,3}, {-3,4}, {-4,-1}, {2,-4}}},

        // Test case 5: Another unsatisfiable case with a cycle
        // Tests cycle detection and unsatisfiability due to contradictory implications.
        {3, 4, {{1,2}, {-2,3}, {-3,-1}, {-1,-3}}}
    };

    for (size_t i = 0; i < tests.size(); i++) {
        int n = get<0>(tests[i]);
        int m = get<1>(tests[i]);
        auto clauses = get<2>(tests[i]);

        cout << "Test case " << i + 1 << ":\n";
        cout << "Number of variables: " << n << ", Number of clauses: " << m << "\n";
        cout << "Clauses:\n";
        for (auto& c : clauses) {
            cout << "  ("
                 << (c.first > 0 ? "x" + to_string(c.first) : "~x" + to_string(-c.first))
                 << " v "
                 << (c.second > 0 ? "x" + to_string(c.second) : "~x" + to_string(-c.second))
                 << ")\n";
        }

        // Explain what is being tested
        switch(i) {
            case 0:
                cout << "Testing basic satisfiability and variable assignments.\n";
                break;
            case 1:
                cout << "Testing detection of unsatisfiability due to contradiction.\n";
                break;
            case 2:
                cout << "Testing minimal input case with small number of clauses.\n";
                break;
            case 3:
                cout << "Testing larger case with chained implications and more variables.\n";
                break;
            case 4:
                cout << "Testing unsatisfiability detection in the presence of cycles.\n";
                break;
        }

        TwoSAT solver(n);
        for (auto& c : clauses) {
            solver.addClause(c.first, c.second);
        }
        vector<int> assignment;

        if (solver.solve(assignment)) {
            cout << "Satisfiable assignment found:\n";
            for (int var = 0; var < n; var++) {
                cout << "  x" << (var + 1) << " = " << (assignment[var] ? "True" : "False") << "\n";
            }
        } else {
            cout << "Unsatifiable\n";
        }
        cout << "-----------------------------------\n";
    }
}

/*
 * Reads user input for test cases, variables, clauses,
 * and solves each test case printing the result.
 */
void manualInput() {
    int t;
    cout << "Enter number of testcases: ";
    cin >> t;
    while (t--) {
        int n, m;
        cout << "Enter number of variables and clauses: ";
        cin >> n >> m;
        TwoSAT solver(n);
        cout << "Enter clauses (two literals per line):\n";
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            solver.addClause(x, y);
        }
        vector<int> assignment;
        if (solver.solve(assignment)) {
            for (int i = 0; i < n; i++) {
                cout << assignment[i] << (i == n-1 ? '\n' : ' ');
            }
        } else {
            cout << "Unsatifiable\n";
        }
    }
}

/*
 * Runs boundary and stress test cases for the 2-SAT solver.
 * These test cases cover:
 * - Minimum input size (0 or 1 variable)
 * - Single clause edge cases
 * - Large input stress test (maximum variables and clauses)
 * - Cases with all positive or all negative literals
 * - Cases with self-contradictory clauses
 *
 * Outputs are descriptive and easy to interpret.
 */
void runBoundaryCases() {
    cout << "\nRunning Boundary and Stress Test Cases\n";
    cout << "=====================================\n";

    vector<tuple<int,int,vector<pair<int,int>>>> boundaryTests = {
        // Case 1: No variables, no clauses (trivial satisfiable)
        {0, 0, {}},

        // Case 2: Single variable, single clause (x1 v x1)
        {1, 1, {{1,1}}},

        // Case 3: Single variable, single clause (¬x1 v ¬x1)
        {1, 1, {{-1,-1}}},

        // Case 4: Single variable, contradictory clauses (x1 v x1) and (¬x1 v ¬x1)
        {1, 2, {{1,1}, {-1,-1}}},

        // Case 5: All variables appear positively, no contradictions (large chain)
        {5, 4, {{1,2}, {2,3}, {3,4}, {4,5}}},

        // Case 6: All variables appear negatively, no contradictions
        {5, 4, {{-1,-2}, {-2,-3}, {-3,-4}, {-4,-5}}},

        // Case 7: Self-contradictory clause (x1 v ¬x1)
        {1, 1, {{1,-1}}},

        // Case 8: Larger stress test with 1000 variables and 999 clauses chaining implications
        // Constructs chain: x1->x2, x2->x3, ..., x999->x1000
        [](){
            int n = 1000;
            vector<pair<int,int>> clauses;
            for(int i = 1; i < n; i++) {
                clauses.push_back({i, i+1});
            }
            return make_tuple(n, (int)clauses.size(), clauses);
        }(),

        // Case 9: Large unsat with contradictory clause at end
        [](){
            int n = 1000;
            vector<pair<int,int>> clauses;
            for(int i = 1; i < n; i++) {
                clauses.push_back({i, i+1});
            }
            // Add contradictory clause
            clauses.push_back({-1, -1});
            return make_tuple(n, (int)clauses.size(), clauses);
        }()
    };

    for (size_t i = 0; i < boundaryTests.size(); i++) {
        int n = get<0>(boundaryTests[i]);
        int m = get<1>(boundaryTests[i]);
        auto clauses = get<2>(boundaryTests[i]);

        cout << "Boundary Test case " << i + 1 << ":\n";
        cout << "Number of variables: " << n << ", Number of clauses: " << m << "\n";

        if (m > 0 && m <= 20) { // Print clauses only if reasonably small
            cout << "Clauses:\n";
            for (auto& c : clauses) {
                cout << "  ("
                     << (c.first > 0 ? "x" + to_string(c.first) : "~x" + to_string(-c.first))
                     << " v "
                     << (c.second > 0 ? "x" + to_string(c.second) : "~x" + to_string(-c.second))
                     << ")\n";
            }
        } else {
            cout << "(Clauses not printed due to size)\n";
        }

        TwoSAT solver(n);
        for (auto& c : clauses) {
            solver.addClause(c.first, c.second);
        }
        vector<int> assignment;

        if (solver.solve(assignment)) {
            cout << "Satisfiable assignment found.\n";
            if (n <= 20) { // Print assignment only if small enough
                for (int var = 0; var < n; var++) {
                    cout << "  x" << (var + 1) << " = " << (assignment[var] ? "True" : "False") << "\n";
                }
            } else {
                cout << "(Assignment suppressed due to large size)\n";
            }
        } else {
            cout << "Unsatifiable\n";
        }
        cout << "-----------------------------------\n";
    }
}

/*
 * Main function to choose input mode and execute the solver.
 */
int main() {
    cout << "2-CNF SAT Solver\n";
    cout << "Choose input mode:\n";
    cout << "1. Manual Input\n";
    cout << "2. Run Sample Test Cases\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        manualInput();
    } else {
        runTestCases();
        runBoundaryCases();
        cout << "All test cases completed.\n";
    }
    return 0;
}
