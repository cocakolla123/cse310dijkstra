# cse310dijkstra
1. Make
2. ./dijkstra <filename> <direction>
    - file has to be a text file with the format of network01.txt where the first line is the number of edges then
      vertices and the lines under are the edges with the vertices they are connecting and the weight of the edge
    - direction has to be either directed or undirected
3. Queries
   - find <source> <destination> <flag>
     Denote by source, destination, and flag the values of <source>, <destination>, and <flag>, respectively. This
     query is valid if source ∈ V , destination is an integer not equal to source, and flag ∈ {0, 1}. If the query
     is not valid, your program should write a message to stdout using the following format and wait for the next query.
   - write path <s> <d>
     The answer to this query is based on the computed information by the most recent valid find query: find <source> <destination> <flag>
     Denote by s and d the values of <s> and <d>, respectively, in this write query. Denote by source and
     destination the values of <source> and <destination>, respectively, in the most recent valid find
     query, if there has been one. Your program should act as follows.
   - stop
     Your program exits gracefully. This means that you should free all memory that you dynamically
     allocated before exiting the program.
