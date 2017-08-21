#for i in range(0, 7) :
#    
#    iEta = round(-15 + 5.0/7.0*i)
#    print i, iEta
#
#print "***"
#
#for i in range(0, 7) :
#    
#    iEta = round(-10 + 6.0/7.0*i)
#    print i, iEta
#
#print "***"
#
#for i in range(0, 7) :
#    
#    iEta = round(-4 + 8.0/7.0*i)
#    print i, iEta
#
#print "***"
#
#for i in reversed(range(0, 7)) :
#    
#    iEta = round(4 - 8.0/7.0*i)
#    print i, iEta
#
#print "***"
#
#for i in reversed(range(0, 7)) :
#    
#    iEta = round(10 - 6.0/7.0*i)
#    print i, iEta
#
#print "***"
#
#for i in reversed(range(0, 7)) :
#    
#    iEta = round(15 - 5.0/7.0*i)
#    print i, iEta

#for i in range(0, 72) :
#    
#    j = ((i+2)%6)
#    k = i%6
#    print i, j, k, ";", i+1, j+1, k+1
#    
#    if ((j+1) % 6 == 0) :
#        
#        print "--------------------"

for i in range(1, 73) :
    
    j = (i-1+2) % 72
    
    print i, j, j+1, int(j/6.0 + 1)
