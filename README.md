The Palette-Enumerator project is a tool to enumerate Palettes of Halin tripoles. This is the computational part of the article **Total coloring of (sub)cubic Halin graph**, preprint: https://arxiv.org/abs/2603.23189 .

**Installation**:
- Download the repository and simply execute "make enumerator". Then simply run by "./enumerator --params".

By default, (total colouring) palettes of all Halin tripoles upto a given rank (parameter) are outputed. There are two mandatory arguments: output file and depth (maximal rank of the tripole). The following call will print all palettes of Halin tripoles upto rank 4 into file output.txt: "./enumerator output.txt 4". The output contents can further be changed by the following flags.

 * -b = prints bitmap, otherwise prints quadruples (default)
 * -f = print tripoles with full pallets
 * -r = print reducible pairs; i. e. pairs with same pallet
 * -u = generate only tripoles with unique pallets, discard the rest
 * -n = only prints the number of tripoles on each tier
 * -N = prints only non-colourable halin graphs
 * -p = prints pallete parent count for each tripole, forces -u, as otherwise it does not make much sense 
 * -P (capital) = prints pallete parents for each tripole, forces -u
 * -s = generate sub-cubic graphs
 * -a = AVD colouring
 * -A = SND colouring
 
 The flags can be concatenated into a single string, hence for example "./enumerator output.txt 10 -sau" will write AVD-palettes of all subcubic Halin tripoles that are unique, in other words, all AVD-palettes in stratum 10 or smaller.

**Implementation details**:

A palette $P$ of Halin tripole -- set of sextuples $T \subset \{0,1,2,3\}^6$ contains a lot of redundancy. Consider a permutation $\sigma \in S_4$. Then if $(a,b,c,d,e,f) \in P$ it implies that $(\sigma(a),\sigma(b),\sigma(c),\sigma(d),\sigma(e),\sigma(f)) \in P$ as well. Therefore, a color $0$ can be permanently prescribed to the root semi-edge, and color $1$ to the root vertex. An extendable coloring can then be represented as a quadruple -- colors around peripheral semi-edges. A palette $P$ can then be represented as a binary matrix $M$ with $M_{4a+b, 4c+d} = 1$ and $0$ otherwise. To reference such matrix we simply denote $M(P_1)$ to be the matrix of the palette $P_1$. The composition of two palettes can then be done as operations over this matrix.

When doing a composition of two (quad-)palettes the root semi-edges are now both colored 0 and so is the new root edge of the bigger tripole corresponding to this palette. Therefore, you firstly need to recolor the palettes so that the root semi-edges of the sub-palettes have colors different from $0$ (color of the new root semi-edge), $1$ (color of the new root vertex) and the color of the semi-edge in the other sub-palette. Similarly, the root vertex must be recolored to a color different from $1$ and the new color of the root semi-edge in the subtripole. This is simply done by renaming the colors, i.e. transforming the palette by a set of permutations from $S_4$.

Secondly, you want to compose such recolored palettes. Observe that if $(a,b,c,d) \in P_1$ and $(c,e,f,g) \in P_2$, then $(a,b,f,g) \in P$ (provided $d \neq e$). Therefore, the element $(a,b,c,d)$ from $P_1$ can only be paired with precolorings starting with $(c,x,..)$ (we have precisely two distinct values for $x$), therefore, the elements it can pair with can only be found in columns $M_{4c+x}$ of the matrix of $P_2$. Now, for every $1$ on position $4f+g$ in column $M_{4c+x}$ we would have $1$ in the same position, but in the column $4a+b$ in the matrix of the composed palette (since $(a,b,f,g) \in P$). We do this in two steps. Firstly, for each $M_{4a+b,4c+d} = 1$ in $P_1$ we precompute the columns it can pair with. In other words we apply the function $\mu$ to each column (binary vector of length 16). Formally, $M_{4a+b,4c+d} = 1 \implies M_{4a+b, 4c+x} = M_{4a+b, 4c+y} = 1$. Now that we have $\mu(M(P_1))$ and $M(P_2)$, we can simply compose the $M(P)$ by doing binary OR between $M(P)$ and $M(P_2)$, whenever there is 1 in $\mu(M(P_1))$. Observe that this is simply a multiplication of the binary matrices $\mu(M(P_1))$ and $M(P_2)$.
 
The program is divided into 3 main files:

- _enumerator\_util.cpp_ - contains auxiliary functions
- _enumerator\_premapper.cpp_ - contains functions responsible for precomputing functions for recoloration and pairing ($\mu$).
- _enumerator.cpp_ - combines the logic and handles the input and output. 
