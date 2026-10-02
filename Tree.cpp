#include <iostream>
using namespace std;

// struktur untuk satu simpul (node) pada tree
// menyimpan nilai dan alamat anak kiri serta anak kanan
struct Node {
    int data;
    Node *kiri;
    Node *kanan;
};

// alokasi memori untuk simpul baru di heap, anaknya belum ada (NULL)
Node* buatNode(int nilai) {
    Node *baru = new Node;
    baru->data = nilai;
    baru->kiri = nullptr;
    baru->kanan = nullptr;
    return baru;
}

// cari posisi yang tepat untuk nilai baru, lalu pasang di sana
Node* sisip(Node *root, int nilai) {
    // posisi kosong ketemu (atau tree masih kosong), buat simpul di sini
    if (root == nullptr) {
        return buatNode(nilai);
    }
    // nilai lebih kecil dari simpul saat ini, telusuri cabang kiri
    if (nilai < root->data) {
        root->kiri = sisip(root->kiri, nilai);
    }
    // nilai lebih besar dari simpul saat ini, telusuri cabang kanan
    else if (nilai > root->data) {
        root->kanan = sisip(root->kanan, nilai);
    }
    // jika sama, tidak dimasukkan lagi supaya tidak ada nilai kembar
    return root;
}

// pre-order: kunjungi simpul dulu, baru anak kiri, lalu anak kanan
void preOrder(Node *root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    preOrder(root->kiri);
    preOrder(root->kanan);
}

// in-order: anak kiri dulu, lalu simpul, baru anak kanan
// (hasilnya selalu terurut naik pada BST)
void inOrder(Node *root) {
    if (root == nullptr) return;
    inOrder(root->kiri);
    cout << root->data << " ";
    inOrder(root->kanan);
}

// post-order: kedua anak dulu (kiri lalu kanan), simpul paling akhir
void postOrder(Node *root) {
    if (root == nullptr) return;
    postOrder(root->kiri);
    postOrder(root->kanan);
    cout << root->data << " ";
}

// bebaskan semua memori simpul dari bawah ke atas (pola post-order)
void hapusTree(Node *root) {
    if (root == nullptr) return;
    hapusTree(root->kiri);
    hapusTree(root->kanan);
    delete root;
}

int main() {
    Node *root = nullptr;   // awalnya tree belum punya simpul
    int angka;

    cout << "Masukkan angka (ketik 0 untuk selesai):" << endl;

    // terus baca input sampai pengguna mengetik 0
    while (true) {
        cout << "> ";
        cin >> angka;
        if (angka == 0) break;
        root = sisip(root, angka);   // angka pertama otomatis menjadi root
    }

    // kalau langsung ketik 0, tidak ada yang bisa ditampilkan
    if (root == nullptr) {
        cout << "Tree kosong." << endl;
        return 0;
    }

    // tampilkan ketiga jenis penelusuran
    cout << "\nPre-order  : ";
    preOrder(root);
    cout << "\nIn-order   : ";
    inOrder(root);
    cout << "\nPost-order : ";
    postOrder(root);
    cout << endl;

    hapusTree(root);   // bersihkan memori sebelum program berakhir
    return 0;
}
