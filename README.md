# junglebplus


# ✏️ Binary Search Tree
![](https://images.velog.io/images/jewelrykim/post/c06eb9a7-df9d-4b79-ae10-a0885b132c84/binarysearchtree.png)
이진 탐색 트리(Binary Search Tree, BST)는 이진탐색과 연결리스트(Linked List)를 결합한 자료구조이다. 
- 이진탐색
장점 : 탐색에 소요되는 시간복잡도는 O(log n)으로 빠름
- 연결리스트
장점 : 자료 입력, 삭제에 필요한 시간복잡도는 O(1)로 빠름
단점 : 탐색하는데 O(n)의 시간복잡도를 가짐.

이진 탐색 트리는 이 둘의 장점을 합쳐보고자 만들어진 자료구조이다. 

### 하지만
![](https://images.velog.io/images/jewelrykim/post/07b6c65b-c94f-4d67-88b8-29c67d1a1713/%E1%84%8B%E1%85%B5%E1%84%8C%E1%85%B5%E1%86%AB%E1%84%90%E1%85%A1%E1%86%B7%E1%84%89%E1%85%A2%E1%86%A8%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%20%E1%84%87%E1%85%A2%E1%86%AF%E1%84%85%E1%85%A5%E1%86%AB%E1%84%89%E1%85%B3.png)

오른쪽 그림과 같이 균형이 잡힌 이진 탐색 트리의 경우 시간복잡도가 이진탐색의 시간복잡도인 O(log n)이 되지만, 왼쪽 그림과 같이 균형이 잡히지 않은 이진 탐색의 경우 O(n)에 수렴하게 되면서 이진탐색의 장점을 가졌다고 보기 어려웠다. 

### 그래서 이를 해결하기 위한 여러 자료구조가 탄생했고 그중에 B tree가 있다.

# ✏️ B tree 
![](https://images.velog.io/images/jewelrykim/post/15235c95-ad33-4ae8-b14c-cbcb0046b724/b-tree.png)
- 데이터베이스와 파일시스템에서 많이 사용하는 자료구조이다.
- B-Tree는 이진 트리와 달리 자식노드의 개수가 2개이상인 트리이다.
- 노드 내의 데이터가 1개 이상일 수 있다. 
- 노드의 데이터 수가 n개라면 자식 노드의 개수는 n+1개이다.(초기 root의 경우나 leaf노드 제외)
- 이진 탐색 트리와 다르게 balance가 맞춰져있는 자료구조이다.

### 탐색
- 이진트리와 마찬가지로 왼쪽에 작은 값, 오른쪽에 큰 값으로 이루어져있다.
- 찾고자 하는 값을 root노드부터 시작해 하향식으로 탐색해나간다.
- 최악의 경우에도 O(log n)의 시간복잡도를 가진다.

### 삽입
- 차수에 따라 알고리즘이 다르다.
- 삽입되는 데이터는 항상 leaf노드에 추가된다.
- 추가될 leaf노드에 여유가 있다면 삽입한다.
- 추가될 leaf노드에 여유가 없다면 노드 데이터 중 (node/2)를 부모노드로 옮기고 좌우로 분할한 뒤에 삽입한다.

#### 1~5까지 삽입했을 때의 트리구조
![](https://images.velog.io/images/jewelrykim/post/06c27923-f37c-4921-a8d4-ed042f9a65a3/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.04.00.png)

#### 6을 추가로 삽입했을 때의 트리구조
![](https://images.velog.io/images/jewelrykim/post/2fa1b7bc-51f8-478e-a3a7-1ca6f5fdc365/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.04.49.png)

- n/2인 4(4개 중 2번째)가 부모노드로 올라가고 3,5,6이 좌우로 분할된 것을 볼 수 있다.

[B-Tree시각화 홈페이지에서 직접해보기](https://www.cs.usfca.edu/~galles/visualization/BTree.html)

### 삭제
- 삭제하고자 하는 자료가 있는 노드가 삭제된 후에도 N/2이상이 되도록 보장해야함
- 또한 차수에 따라 알고리즘이 다르다.(홀수, 짝수)
#### 삭제하려는 키가 leaf node에 있을 경우
1 . 키가 삭제된 뒤에도 node의 자료수가 n/2이상일 경우 그냥 삭제한다.
2 . 키가 삭제된 뒤에 node의 자료수가 n/2 미만일 경우, 형제 node로 부터 값을 빌려온다.
3 . 키가 삭제된 뒤에 node의 자료수가 n/2 미만임과 동시에 형제 node로 부터도 값을 빌려올 수 없는 경우(형제 node도 n/2미만이 될 경우) 형제노드와 합병한다.(merge)

#### 예시
![](https://images.velog.io/images/jewelrykim/post/1547d9ab-2a90-4b94-8720-35247d126dbe/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.14.29.png)
#### 여기서 5를 삭제한다면?
![](https://images.velog.io/images/jewelrykim/post/b245a837-a399-4049-81d2-b6eb82f88dc9/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.15.49.png)
#### 부모의 6이 내려오고 오른쪽 형제의 7이 부모로 올라간다. 그렇다면 여기서 1을 삭제한다면?
![](https://images.velog.io/images/jewelrykim/post/ecd2162a-eacc-4736-97cc-516af423cf27/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.17.23.png)
#### 오른쪽 형제도 빌려올 값이 없으므로(n/2미만) 합병이 되고 부모의 노드 데이터 수는 1이 줄어들게 된다.(3에서 2로)

### B-Tree의 장단점
- 장점
1 . 삽입, 삭제 후에도 균형트리가 유지된다.
2 . 균등한 탐색 속도가 보장된다. (최악의 경우 O(log n)의 시간복잡도)
- 단점
1 . 트리균형을 위해서 복잡한 연산이 필요하다.(재분배, 합병)
2 . 순차탐색 시 비효율적이다. 중위순회를 하기때문.
#### 중위순회방법(왼쪽 하위트리로부터 뿌리 -> 오른쪽 트리 순)
![](https://images.velog.io/images/jewelrykim/post/5ae14e3c-e184-47ed-af8f-4b23d6860c28/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.29.24.png)
#### 중위순회를 한다면 7->3->8->1->9->4->10->0->11->5->2->6


### B-tree의 순차탐색을 효율적으로 하기위해 B+tree가 등장하였다.

# ✏️ B+ tree
![](https://images.velog.io/images/jewelrykim/post/324a1be8-2683-452e-a36f-97326c416b9a/Bplustree.png)
### B tree와의 차이점
- B-tree에서는 특정 key값이 하나의 노드에서만 존재할 수 있었지만 B+tree에서는 leaf노드와 부모 노드에 공존할 수 있다.
- 데이터는 leaf노드에만 존재한다.
- leaf노드가 아닌 노드는 데이터의 빠른 접근을 위한 인덱스 역할만 수행한다.(key와 pointer로만 구성)
- 핵심 : leaf노드들은 연결리스트 형태로 서로 연결되어 있고 오름차순으로 정렬되어있다.(순차탐색에 효율적인 이유)

### 삽입
- leaf와 부모에 키가 중복되어 존재하며, 연결리스트 형태로 leaf노드들이 연결되어 있다.
- 노드 overflow시 분할되어 부모로 올라가는 값은 n/2 + 1의 값이다.
#### 예시
![](https://images.velog.io/images/jewelrykim/post/a3804c65-bbd3-473b-9e53-46bd6a2242ce/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.40.34.png)
#### 여기서 4를 삽입한다면
![](https://images.velog.io/images/jewelrykim/post/1d9361da-cf17-46ca-9d88-a419e33800dc/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.40.58.png)
#### 이런식으로 n/2 + 1 인 3이 부모로 올라가고 분할하게 됨과 동시에 연결리스트가 형성된다.

[B+tree 시각화 홈페이지에서 직접해보기](https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html)

### 삭제
- 키 값을 삭제했을 때 leafnode가 underflow 되지 않는다면, 키값을 삭제하고 부모에서도 값을 삭제 후 적절한 key를 그 자리에 넣는다.
- 키값을 삭제했을 때 leafnode가 underflow가 되면 형제노드로부터 값을 빌리거나 병합한다.(B-tree와의 유사점)
#### 예시
![](https://images.velog.io/images/jewelrykim/post/ef789097-8001-4eb2-82c4-e14c7b8764b1/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.43.30.png) 
#### 여기서 8을 삭제한다면
![](https://images.velog.io/images/jewelrykim/post/fd430e58-09c6-4a86-8a99-0678c00ed997/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.44.15.png)

#### 여기서 7을 삭제한다면
![](https://images.velog.io/images/jewelrykim/post/b2cb501d-4f71-45fe-bb49-3d350396d2f0/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.44.51.png)

#### 여기서 9를 삭제한다면
![](https://images.velog.io/images/jewelrykim/post/53468243-0836-4f50-8792-02c5f4b93f62/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.47.12.png)

### 데이터 탐색의 시간복잡도
B-tree와의 차이점 중에 하나이다. B-tree는 최악의 경우 O(log n)의 탐색 시 시간복잡도를 가졌는데 반해 B+tree의 경우는 어떤 경우라도 동일하게 leaf node까지 데이터를 탐색하러 하향해야하기 때문에 항상 O(log n)의 시간복잡도를 갖는다. 따라서 B-tree에서 자주 access 되는 노드를 루트 가까이에 배치한다면 B-tree에서는 더 빠른 속도를 가질 수 있다. 반면, B+tree에서 루트에서 탐색한다면 더 빠른 속도는 불가능한 방법이다.


# ✏️ Database Index
![](https://images.velog.io/images/jewelrykim/post/dc53b03e-3042-498b-9681-81915cd76cd7/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202021-04-24%20%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE%205.57.15.png)

Database index는 데이터의 검색속도를 향상시키기 위한 자료구조이다. 데이터의 검색속도를 빠르게 해줄 수 있다. 자료를 조회하는 SELECT외에도 UPDATE, DELETE 등 자료 색인이 선행되는 연산에서도 더 빠른 속도를 보여준다.

### 인덱스 자료구조 추가에 따른 추가 연산

- INSERT : 새로운 데이터에 대한 인덱스를 추가함.
- DELETE : 삭제하는 데이터의 인덱스를 사용하지 않는다는 작업을 진행함.
- UPDATE : 기존의 인덱스를 사용하지 않음 처리하고, 갱신된 데이터에 대해 인덱스를 추가함.

### 인덱스의 장점, 단점

- 장점
    - 테이블을 조회하는 속도와 그에 따른 성능을 향상시킬 수 있다.
    - 전반적인 시스템의 부하를 줄일 수 있다.
- 단점
    - 인덱스를 관리하기 위해 DB의 추가 저장공간이 필요하다.
    - 인덱스를 관리하기 위해 추가 작업이 필요하다.
    - 인덱스를 잘못 사용하는 경우 오히려 성능이 저하되는 역효과가 발생할 수 있다.

#### 오히려 성능이 저하되는 경우?

CREATE, DELETE, UPDATE가 빈번한 속성에 인덱스를 사용하게 되면 인덱스의 크기가 비대해져서 성능이 오히려 저하되는 역효과가 발생할 수 있다. 그러한 이유 중 하나는 DELETE, UPDATE 연산 때문이다. 왜냐하면 UPDATE, DELETE는 기존의 인덱스를 삭제하지 않고 '사용하지 않음' 처리를 함. 그래서 UPDATE, DELETE가 빈번하게 발생하면 실제 데이터보다 인덱스가 더 커질 수 있다. 비대해진 인덱스를 처리할 때 더 성능이 떨어질 수 있다.

#### 그래서 인덱스를 사용하면 좋은 경우

- 규모가 작지 않은 테이블
- INSERT, UPDATE, DELETE가 자주 발생하지 않는 컬럼
- JOIN이나 WHERE 또는 ORDER BY에 자주 사용되는 컬럼
- 데이터의 중복도가 낮은 컬럼

#### 인덱스의 자료구조

- 해시테이블
    - 시간복잡도 O(1)
    - 하지만 해쉬는 제한적임. 등호 (=) 연산에 특화되어있음. 1이라도 값이 다르면 다른 해시값을 생성하기 때문에 >,< 연산이 자주 사용되는 DB검색에 해시테이블은 적합하지 않다.

- B+ Tree
    - 모든 노드에 데이터를 저장하는 BTree와 달리 리프에만 데이터를 가지고 있고 나머지 노드는 인덱스만 같는다.
    - 단점은 무조건 리프노드까지 가야함
    - 장점은 링크드리스트라서 순차검색이 용이함
    - 시간복잡도는 O(log n)