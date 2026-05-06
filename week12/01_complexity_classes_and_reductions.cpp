/*
 * ============================================================================
 *  COMPLEXITY CLASSES & POLYNOMIAL TIME REDUCTION
 * ============================================================================
 *  1. DECISION PROBLEMS:
 *     - A problem with a YES or NO answer. (e.g., "Is there a path of length 
 *       <= K?" instead of "What is the shortest path?").
 *     - Complexity classes usually deal with decision problems.
 *
 *  2. COMPLEXITY CLASSES:
 *     - P (Polynomial Time): Problems that can be SOLVED in polynomial time 
 *       O(n^k) by a deterministic Turing machine. (e.g., Shortest Path, MST).
 *     - NP (Nondeterministic Polynomial Time): Problems where a YES answer 
 *       can be VERIFIED in polynomial time given a "certificate" (a proposed 
 *       solution). 
 *       (e.g., If I give you a path and claim it's length <= K, you can easily 
 *       verify my claim in polynomial time).
 *     - NP-Hard: A problem is NP-Hard if every problem in NP can be reduced 
 *       to it in polynomial time. (They are "at least as hard as the hardest 
 *       problems in NP").
 *     - NP-Complete: A problem that is BOTH in NP and NP-Hard.
 *
 *  3. POLYNOMIAL-TIME REDUCTION (A <=p B):
 *     - Transforming an instance of Problem A into an instance of Problem B 
 *       in polynomial time, such that Answer(A) is YES iff Answer(B) is YES.
 *     - If A <=p B and B is in P, then A is in P.
 *     - If A is NP-Hard and A <=p B, then B is NP-Hard.
 *
 *  EXAM TIP:
 *  - P is a subset of NP. (If you can solve it in poly-time, you can certainly 
 *    verify it in poly-time).
 *  - Million Dollar Question: Does P = NP? (Is generating a solution as easy 
 *    as verifying one?)
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

// ─────────────────────────────────────────────────────────────────────────────
//  NP CONCEPT: POLYNOMIAL TIME VERIFICATION
// ─────────────────────────────────────────────────────────────────────────────
// Problem: Does the graph contain a Vertex Cover of size <= K?
// This is an NP-Complete problem. Finding the cover is hard (exponential time),
// but VERIFYING a proposed cover (the "certificate") takes polynomial time.

// Verifier Function: Takes the graph and a proposed set of vertices (certificate).
// Time Complexity: O(E) which is Polynomial -> Therefore, Vertex Cover is in NP.
bool verifyVertexCoverCertificate(int V, const vector<pair<int, int>>& edges, const vector<int>& certificate, int K) {
    if (certificate.size() > K) {
        cout << "Verification failed: Certificate size exceeds K.\n";
        return false;
    }

    // Convert certificate to a hash set for O(1) lookups
    unordered_set<int> cover(certificate.begin(), certificate.end());

    // Check if every edge is covered by at least one vertex in the certificate
    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        
        if (cover.find(u) == cover.end() && cover.find(v) == cover.end()) {
            cout << "Verification failed: Edge (" << u << ", " << v << ") is not covered.\n";
            return false;
        }
    }

    cout << "Verification successful: The provided certificate is a valid vertex cover of size <= " << K << ".\n";
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== NP VERIFICATION EXAMPLE ===\n";
    
    int V = 5;
    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 4}, {3, 4}
    };

    int K = 3;

    // Certificate 1: A valid vertex cover {0, 1, 4}
    vector<int> valid_cert = {0, 1, 4};
    cout << "Testing Certificate 1 {0, 1, 4}:\n";
    verifyVertexCoverCertificate(V, edges, valid_cert, K);

    cout << "\n";

    // Certificate 2: An invalid vertex cover {0, 3} (misses edge 1-2 and 2-4)
    vector<int> invalid_cert = {0, 3};
    cout << "Testing Certificate 2 {0, 3}:\n";
    verifyVertexCoverCertificate(V, edges, invalid_cert, K);

    return 0;
}
