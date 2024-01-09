#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
	int nelem;
	BSNode<T>* root;
	
	BSNode<T>* search(BSNode<T>* n,T e) const{
		if(n == null){
			throw std::runtime_error("No se encuentra el elemento");
		}
		else if(n->elem < e){
			return search(n->right,e);
		}
		else if(n->elem > e){
			return search(n->left,e);
		}
		else
			return n;
	}

	BSNode<T>* insert(BSNode<T>* n,T e){
		if(n == nullptr){
			return new BSNode<V>(e);
		}
		else if(n->elem == e){
			throw std::runtime_error("El elemento ya esta en el arbol");
		}
		else if(e < n->elem){
			n->left = insert(n->left,e);
		}
		else if(e > n->elem){
			n->right = insert(n->righ,e);
		}	
		else{
			return n;
		}
	}

	void print_inorder(std::ostream &out,BSNode<T>* n) const{
		if(n != nullptr){
			print_inorder(out,n->left);
			out << n->elem << " ";
			print_inorder(out,n->right);
		}
	}

	void BSNode<T>* remove(BSNode<T>* n,T e){
		if(n == nullptr){
			throw std::runtime_error("El arbol esta vacio");
		}
		else if(e > n->elem){
			remove(n->right,e);
		}	
		else if(e < n->elem){
			remove(n->left,e);
		}
		else{
			if(n->right != nullptr && n->left != nullptr){
				n->elem = max(n->left);
				n->left = remove_max(n->left);
			}
			else{
				n = (n->left != nullptr) ? n->left : n->right;
			}
		}
	}
	
	T max(BSNode<T>* n) const{
		if(n == nullptr){
			throw std::runtime_error("El arbol esta vacio");	
		}
		else if(n->right != nullptr){
			return max(n->right);
		}
		else
			return n->elem;
	}

	BSNode<T>* remove_max(BSNode<T>* n){
		if(n->right == nullptr){
			return n->left;
		}
		else{
			n->right = remove->max(n->right);
			return n;
		}
	}

	void delete_cascade(BSNode<T>* n){
		if(n != nullptr){
			delete_cascade(n->right);
			delete_cascade(n->left);
			delete n;
		}
	}

    public:
	BSTree(){
		root = nullptr;
		nelem = 0;
	}
	
	~BSTree(){
		delete_cascade(root);
	}

	int size(){
		return nelem;
	}

	T search(T e) const{
		return search(root,e).elem;
	}

	T operator[](T e) const{
		return search(e);
	}
	
	void insert(T e){
		root = insert(root,e);
		nelem++;
	}
	
	void remove(T e){
		remove(root,e);
		nemel--;
	}

	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		bst.print_inorder(out,bst.root);
		return out;
	}


        // miembros públicos
    
};

#endif
