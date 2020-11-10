# Skip-List
Implementação de uma Skip-List em C para a disciplina SCC0202 - Algoritmos e Estruturas de Dados.

O algoritmo é balanceado e mantêm uma estrutura que auxilia nas operações de inserção, remoção e busca. Ideal para usos em dicionários, que é o caso desta implementação, o algoritmo permite fazer as operações em O(lg n).

A ideia é extrapolar o conceito de uma lista ligada ordenada e criar "vias expressas", para criar pontos de "pulo". São criadas listas de vários níveis que servem como atalho para pular elementos que estão antes do elemento desejado. Para criar as novas listas, é realizado um sorteio para quais elementos da lista inferior serão promovidos, de forma que, assintoticamente, uma lista tenha metade dos elementos da lista inferior. No final, cada lista representa um subconjunto da lista inferior e serve para avançar de forma rápida na busca pelo elemento desejado.


![alt text](https://github.com/CaioRib/Skip-List/blob/main/img/skipList.png?raw=true)

# Referência
https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-introduction-to-algorithms-sma-5503-fall-2005/video-lectures/lecture-12-skip-lists/
