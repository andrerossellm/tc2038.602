# generates buckets
def getBuckets(T): 
    count = {} # count for each character 
    buckets = {} # starting position for the bucket in each char
    # map every char to its count - default to 0 if nonexistent before
    for c in T: 
        count[c] = count.get(c, 0) + 1
    start = 0
    # will auto-sort every char in T (placing $ at the start)
    for c in sorted(count.keys()): 
        buckets[c] = (start, start + count[c]) # maps key = (start, end) of bucket 
        start += count[c] # moves start for bucket of next char
    return buckets

def sais(T):
    t = ["_"] * len(T)
    
    t[len(T) - 1] = "S" #type array with n - 1 predefined as S
    for i in range(len(T) - 1, 0, -1): #type computation 
        if T[i-1] == T[i]:
            t[i - 1] = t[i]
        else:
            t[i - 1] = "S" if T[i-1] < T[i] else "L"
    
    buckets = getBuckets(T) #starting and ending point for every bucket

    #phase 1 - sorts lms positions, may recurse with reduced text
    count = {}
    SA = [-1] * len(T) #generate suffix array
    LMS = {} #LMS positions
    end = None
    for i in range(len(T) - 1, 0, -1): #traverse backwards
        if t[i] == "S" and t[i - 1] == "L": #if find L, S pattern
            revoffset = count[T[i]] = count.get(T[i], 0) + 1 #increment count of T[i]
            SA[buckets[T[i]][1] - revoffset] = i #set ending point for T[i] - count to current pos
            if end is not None: #if there's an ending, mark lms at that pos
                LMS[i] = end
            end = i #assign end to crnt pos

    LMS[len(T) - 1] = len(T) - 1 #last position in LMS set to its index
    count = {}
    for i in range(len(T)): #normal traversal
        if SA[i] >= 0: #for every assigned position
            if t[SA[i] - 1] == "L": #induced sort L positions
                symbol = T[SA[i] - 1]
                offset = count.get(symbol, 0)
                SA[buckets[symbol][0] + offset] = SA[i] - 1
                count[symbol] = offset + 1

    count = {}
    for i in range(len(T) - 1, 0, -1): #traverse backwards
        if SA[i] > 0:
            if t[SA[i] - 1] == "S": #induced sort S positions
                symbol = T[SA[i] - 1]
                revoffset = count[symbol] = count.get(symbol, 0) + 1
                SA[buckets[symbol][1] - revoffset] = SA[i] - 1

    #iterate thru SA and check if substr of T is an LMS 
    #names will store unique names for each LMS substr in string T
    namesp = [-1] * len(T)
    name = 0
    prev = None
    for i in range(len(SA)):
        if t[SA[i]] == "S" and t[SA[i] - 1] == "L": #if LMS by LS pattern
            #if diff from previous LMS substr, increment anme counter, to diff LMSs
            if prev is not None and T[SA[prev]:LMS[SA[prev]]] != T[SA[i]:LMS[SA[i]]]:
                name += 1
            prev = i #sets crnt as last seen LMS 
            namesp[SA[i]] = name #assign computed name

    #names stores unique names for every LMS substr 
    #SApIdx stores indices for every LMS substr in the OG string
    names = []
    SApIdx = []
    for i in range(len(T)):
        if namesp[i] != -1:
            names.append(namesp[i])
            SApIdx.append(i)

    #recursive step to sort names list if necessary
    if name < len(names) - 1:
        names = sais(names)

    names = list(reversed(names)) #reversal

    # sorts all sufixes from correctly sorted LMS
    SA = [-1] * len(T) #reset SA
    count = {}
    for i in range(len(names)): #compute pos of LMS substr in og string
        pos = SApIdx[names[i]]
        revoffset = count[T[pos]] = count.get(T[pos], 0) + 1
        SA[buckets[T[pos]][1] - revoffset] = pos #place the LMS subst in appropriate position by buckets + revoffset

    count = {} #induced sorting for L places
    for i in range(len(T)):
        if SA[i] >= 0:
            if t[SA[i] - 1] == "L":
                symbol = T[SA[i] - 1]
                offset = count.get(symbol, 0)
                SA[buckets[symbol][0] + offset] = SA[i] - 1
                count[symbol] = offset + 1

    count = {} #induced sorting for S places
    for i in range(len(T) - 1, 0, -1):
        if SA[i] > 0:
            if t[SA[i] - 1] == "S":
                symbol = T[SA[i] - 1]
                revoffset = count[symbol] = count.get(symbol, 0) + 1
                SA[buckets[symbol][1] - revoffset] = SA[i] - 1

    #return final SA
    return SA
