### Possible heuristic for determining cycle extendability

* Take all bi-connected chordal graphs (the raw graphs)
* Partition them into two sets (cycle extendable and not cycle extendable)
* Compute the **Algebraic Connectivity** for all graphs
  * The algebraic connectivity of a graph G is the second-smallest eigenvalue of the Laplacian matrix of G.
  * Given a simple graph G with n vertices, its Laplacian matrix L_(n xn) is defined as
    * L = D - A,
    * where D is the degree matrix and A is the adjacency matrix of the graph.
* Cross reference the algebraic connectivity and look for a threshold
