#include <iostream>
#include <queue> // BFS 必须用到队列
using namespace std;

// 1. 定义树节点
struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 2. 插入节点（构建二叉搜索树）
TreeNode* insert(TreeNode* root, int val) {
	if (root == nullptr) return new TreeNode(val);
	
	if (val < root->data) {
		root->left = insert(root->left, val);
	} else if (val > root->data) {
		root->right = insert(root->right, val);
	}
	return root;
}

// 3. 中序遍历（DFS）
void inOrder(TreeNode* root) {
	if (root == nullptr) return;
	inOrder(root->left);
	cout << root->data << " ";
	inOrder(root->right);
}

// 4. 求树的最大深度（DFS）
int maxDepth(TreeNode* root) {
	if (root == nullptr) return 0;
	int leftDepth = maxDepth(root->left);
	int rightDepth = maxDepth(root->right);
	return 1 + max(leftDepth, rightDepth);
}

// 5. 层序遍历（BFS）
void bfs(TreeNode* root) {
	if (root == nullptr) return;
	queue<TreeNode*> q;
	q.push(root);
	
	int level = 1;
	while (!q.empty()) {
		int size = q.size(); // 锁定当前层节点数
		cout << "第 " << level << " 层: ";
		
		for (int i = 0; i < size; i++) {
			TreeNode* node = q.front();
			q.pop();
			cout << node->data << " ";
			
			if (node->left) q.push(node->left);
			if (node->right) q.push(node->right);
		}
		cout << endl;
		level++;
	}
}

int main() {
	TreeNode* root = nullptr;
	int arr[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
	
	// 建树
	for(int i = 0; i < 9; i++) {
		root = insert(root, arr[i]);
	}
	
	cout << "中序遍历(DFS): ";
	inOrder(root);
	cout << endl;
	
	cout << "树的最大深度: " << maxDepth(root) << endl;
	
	cout << "层序遍历(BFS):" << endl;
	bfs(root);
	
	return 0;
}
