/*
 * ============================================================================
 *  BOOLEAN SATISFIABILITY (SAT)
 * ============================================================================
 *  CONCEPTS:
 *  - SAT was the FIRST problem ever proven to be NP-Complete (Cook-Levin Theorem).
 *  - A boolean formula consists of variables (x, y, z), AND, OR, and NOT 
 *    operations. 
 *  - A formula is SATISFIABLE if there is some assignment of TRUE/FALSE to 
 *    variables that makes the entire formula evaluate to TRUE.
 *
 *  CNF (Conjunctive Normal Form):
 *  - AND of ORs. Example: (x OR y) AND (NOT x OR z) AND (y OR NOT z)
 *  - Each (x OR y) is called a CLAUSE.
 *  - 3-SAT: A special case where every clause has exactly 3 variables. 3-SAT 
 *    is NP-Complete. (Interestingly, 2-SAT can be solved in Polynomial time P!).
 *
 *  LABORATORY APPLICATION:
 *  - Solving SAT usually involves backtracking algorithms like DPLL (Davis-
 *    Putnam-Logemann-Loveland) or modern heuristic SAT Solvers.
 *  - Below is a simple recursive backtracking approach to evaluate a small CNF.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <limits>
#include <climits>
#include <cstring>
#include <numeric>

using namespace std;

// Represent a clause as a vector of integers.
// Positive integer 'i' means variable xi.
// Negative integer '-i' means NOT xi.
typedef vector<int> Clause;
typedef vector<Clause> CNFFormula;

// ─────────────────────────────────────────────────────────────────────────────
//  SAT SOLVER (Backtracking)
// ─────────────────────────────────────────────────────────────────────────────
// Evaluates the formula given a specific assignment
// assignment[i] = 1 (True), 0 (False), -1 (Unassigned)
bool evaluateFormula(const CNFFormula& formula, const vector<int>& assignment) {
    for (const auto& clause : formula) {
        bool clause_satisfied = false;
        for (int literal : clause) {
            int var_idx = abs(literal);
            int is_not = literal < 0;

            if (assignment[var_idx] != -1) {
                // If variable is true and literal is positive -> true
                // If variable is false and literal is NOT -> true
                if ((assignment[var_idx] == 1 && !is_not) || 
                    (assignment[var_idx] == 0 && is_not)) {
                    clause_satisfied = true;
                    break;
                }
            }
        }
        if (!clause_satisfied) return false;
    }
    return true;
}

// Backtracking solver
bool solveSAT(const CNFFormula& formula, vector<int>& assignment, int var_idx, int num_vars) {
    // If we've assigned all variables, evaluate the formula
    if (var_idx > num_vars) {
        return evaluateFormula(formula, assignment);
    }

    // Try assigning TRUE
    assignment[var_idx] = 1;
    if (solveSAT(formula, assignment, var_idx + 1, num_vars)) return true;

    // Try assigning FALSE
    assignment[var_idx] = 0;
    if (solveSAT(formula, assignment, var_idx + 1, num_vars)) return true;

    // Backtrack
    assignment[var_idx] = -1;
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    // Let variables be 1 (x), 2 (y), 3 (z)
    int num_vars = 3;
    vector<int> assignment(num_vars + 1, -1); // 1-based indexing

    /*
     * Formula: (x OR y) AND (NOT x OR z) AND (NOT y OR NOT z)
     */
    CNFFormula formula = {
        {1, 2},    // (x OR y)
        {-1, 3},   // (NOT x OR z)
        {-2, -3}   // (NOT y OR NOT z)
    };

    cout << "=== SAT SOLVER (Backtracking) ===\n";
    if (solveSAT(formula, assignment, 1, num_vars)) {
        cout << "Formula is SATISFIABLE!\nAssignment:\n";
        for (int i = 1; i <= num_vars; ++i) {
            cout << "Variable " << i << " = " << (assignment[i] ? "TRUE" : "FALSE") << "\n";
        }
    } else {
        cout << "Formula is UNSATISFIABLE!\n";
    }

    return 0;
}
