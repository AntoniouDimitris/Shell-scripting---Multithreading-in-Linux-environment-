for j = 1:1:6
    i = j+5;
    n = pow2(i);
    A = (rand(n));
    B = (rand(n));
    
    x1 = rand; % tixaios ari8mos gia tis diagwnious
    x2 = rand;
    x3 = rand;
    x4 = rand;
    x5 = rand;
    x6 = rand;
    
    v1 = repmat(x1,1,n);
    v2 = repmat(x2,1,n-1);
    v3 = repmat(x3,1,n-1);
    v4 = repmat(x4,1,n);
    v5 = repmat(x5,1,n-1);
    v6 = repmat(x6,1,n-1);
    
    C = gallery('tridiag',v2,v1,v3)
    D = full(C);
    E = gallery('tridiag',v5,v4,v6)
    G = full(E);
    
    f = @ () mtimes(A,B); % tixaio mitrwo
    timing0(j) = timeit(f)
    
    h = @ () mtimes(D,G);
    timing1(j) = timeit(h)
    
    L = triu(A);
    L1 = triu(B);
    g = @ () mtimes(L,L1); % anw trigwniko
    timing2(j) = timeit(g)

end
 figure
    m = 6:1:11;
    plot(m,timing0,'r-o')
    hold on;
    plot(m,timing1,'b--x');
    plot(m,timing2,'g:*');
    hold off;
    xlabel('m')
    ylabel('timing')
    legend('A*B','D*G','L*L1')
    
 figure
    m = 6:1:11;
    q = 12:2:22;
    elem = pow2(q);
    gf0 = ((elem*6)./timing0);
    gf1 = ((elem*6)./timing1);
    gf2 = ((elem*6)./timing2);
    plot(timing0,gf0,'r-o')
    hold on;
    plot(timing1,gf1,'b--x');
    plot(timing2,gf2,'g:*');
    hold off;
    ylabel('gf')
    xlabel('timing')
    legend('A*B','D*G','L*L1')
    
    
