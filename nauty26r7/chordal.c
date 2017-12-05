#include "gtools.h"

/* This is a pruning function for use with geng.  It causes
geng output to be restricted to chordal graphs.  To use it
you need to compile it together with geng.c like this (assuming
your compiler is gcc). The file nautyW1.a is made by the nauty
distribution. It needs access to the *.h files of nauty, so if
you aren't in that directory you need to include -I directory
before geng.c, where "directory" is where the *.h files are.

gcc -o chordal -O3 -DMAXN=WORDSIZE -DWORDSIZE=32 -DPRUNE=chordless \
    geng.c chordal.c nautyW1.a

All of the options of geng are available when you run it.
*/

static boolean
hasinducedpath(graph *g, int start, setword body, setword last)
/* return TRUE if there is an induced path in g starting at start,
   extravertices within body and ending in last.
 * {start}, body and last should be disjoint. */
{
    setword gs,w;
    int i;

    gs = g[start];
    if ((gs & last)) return TRUE;

    w = gs & body;
    while (w)
    {
        TAKEBIT(i,w);
        if (hasinducedpath(g,i,body&~gs,last&~bit[i]&~gs))
	    return TRUE;
    }

    return FALSE;
}

boolean
chordless(graph *g, int n, int maxn)
/* g is a graph of order n. Return TRUE if there is a
   chordless cycle of length at least 4 that includes
   the last vertex. */
{
    setword all,gn,w,gs;
    int v,s;

    all = ALLMASK(n);
    gn = g[n-1];

    while (gn)
    {
	TAKEBIT(v,gn);
	gs = g[v] & ~(bit[n-1]|g[n-1]);
	while (gs)
	{
	    TAKEBIT(s,gs);
	    if (hasinducedpath(g,s,all&~(g[n-1]|g[v]),gn&~g[v]))
		return TRUE;
	}
    }

    return FALSE;
}
