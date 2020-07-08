#include "headers.h"

bool nidExists(GlobalNode* nodes, int nid)
{
    int tmpNid = my_hash(nodes, nid);
    int id, foundNid, idErr = nodes->idErr;
    register int probingUsed = 0, size = nodes->hashSize;

    while(true)
    {
        // printf("nidExists\n");
        id = nodes->idByNid[tmpNid];
        if( id == INT_MIN )
        {
            return false;
        }else if( id != TOMBSTONE )
        {   //if not toumbstone but other nid with same hash
            foundNid = nodes->nidById[id-idErr];
            if( foundNid == nid ) return true;
        }
        tmpNid += linearProbing;
        tmpNid %= nodes->hashSize;
        probingUsed++;
        if( probingUsed%size == 0 ) return false;
    }
}