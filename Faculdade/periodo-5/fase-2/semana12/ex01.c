// 1 - Insira em uma a?rvore AVL, itens com as chaves apresentadas nos itens a seguir (na ordem em que aparecem). Desenhe a a?rvore resultante da inserc?a?o, sendo que uma nova a?rvore deve ser desenhada quando houver necessidade de balanceamento e dessa forma uma rotac?a?o. Indique qual a rotac?a?o que foi executada. 

// 30, 40, 24, 58, 48, 26, 11, 13, 14
// 20,15,25,10,30,24,17,12,5,3
// 40, 30, 50, 45, 55, 52
// 20, 15, 25, 12, 17, 24, 30, 10, 14, 13
// 20, 15, 25, 12, 17, 30, 26 

/*
SOLUÇÃO:

1. Sequência: 30, 40, 24, 58, 48, 26, 11, 13, 14

Passo a passo:
1. Inserir 30
   30

2. Inserir 40
   30
     \
      40

3. Inserir 24
     30
    /  \
  24    40

4. Inserir 58
     30
    /  \
  24    40
          \
           58

5. Inserir 48
     30
    /  \
  24    40
          \
           58
          /
        48

6. Inserir 26
     30
    /  \
  24    40
    \     \
    26    58
          /
        48

7. Inserir 11
     30
    /  \
  24    40
 /  \     \
11  26    58
          /
        48

8. Inserir 13
     30
    /  \
  24    40
 /  \     \
11  26    58
  \        /
  13     48

9. Inserir 14 (necessita rotação dupla à direita)
     30
    /  \
  13    40
 /  \     \
11  24    58
     \    /
     26  48

2. Sequência: 20,15,25,10,30,24,17,12,5,3

Passo a passo:
1. Inserir 20
   20

2. Inserir 15
   20
  /
15

3. Inserir 25
   20
  /  \
15    25

4. Inserir 10
   20
  /  \
15    25
/
10

5. Inserir 30
   20
  /  \
15    25
/       \
10      30

6. Inserir 24
   20
  /  \
15    25
/     / \
10   24  30

7. Inserir 17
   20
  /  \
15    25
/  \  / \
10 17 24 30

8. Inserir 12
   20
  /  \
15    25
/  \  / \
10 17 24 30
 \
 12

9. Inserir 5 (necessita rotação simples à direita)
   20
  /  \
10    25
/  \  / \
5  15 24 30
   / \
 12  17

10. Inserir 3 (necessita rotação simples à direita)
   20
  /  \
10    25
/  \  / \
5  15 24 30
/  / \
3 12 17

3. Sequência: 40, 30, 50, 45, 55, 52

Passo a passo:
1. Inserir 40
   40

2. Inserir 30
   40
  /
30

3. Inserir 50
   40
  /  \
30    50

4. Inserir 45
   40
  /  \
30    50
     /
   45

5. Inserir 55
   40
  /  \
30    50
     /  \
   45    55

6. Inserir 52 (necessita rotação dupla à esquerda)
   40
  /  \
30    52
     /  \
   50    55
  /
45

4. Sequência: 20, 15, 25, 12, 17, 24, 30, 10, 14, 13

Passo a passo:
1. Inserir 20
   20

2. Inserir 15
   20
  /
15

3. Inserir 25
   20
  /  \
15    25

4. Inserir 12
   20
  /  \
15    25
/
12

5. Inserir 17
   20
  /  \
15    25
/  \
12  17

6. Inserir 24
   20
  /  \
15    25
/  \  /
12 17 24

7. Inserir 30
   20
  /  \
15    25
/  \  / \
12 17 24 30

8. Inserir 10
   20
  /  \
15    25
/  \  / \
12 17 24 30
/
10

9. Inserir 14
   20
  /  \
15    25
/  \  / \
12 17 24 30
/  \
10 14

10. Inserir 13 (necessita rotação dupla à direita)
   20
  /  \
14    25
/  \  / \
12 17 24 30
/  \
10 13

5. Sequência: 20, 15, 25, 12, 17, 30, 26

Passo a passo:
1. Inserir 20
   20

2. Inserir 15
   20
  /
15

3. Inserir 25
   20
  /  \
15    25

4. Inserir 12
   20
  /  \
15    25
/
12

5. Inserir 17
   20
  /  \
15    25
/  \
12  17

6. Inserir 30
   20
  /  \
15    25
/  \    \
12  17   30

7. Inserir 26 (necessita rotação simples à esquerda)
   20
  /  \
15    26
/  \  / \
12 17 25 30
*/

