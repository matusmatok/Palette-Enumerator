The Palette-Enumerator project is a tool to enumerate Palettes of tripoles.

Installation:
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
