// Oscar Esparza
// 12 September 2018
// CSC 152
// randomPermutation.java

class Main {
    public static void main(String[] args) {
        int n = 11; // size of set
        int[] a;    // a[x] holds the value that x maps to

        a = createRandomPermutation(n);

        for(int i = 0; i < n; i++){
            System.out.print(a[i]);
            System.out.print(" ");
        }
    }

    public static int[] createRandomPermutation(int n){
        int[] a;
        a = new int[n];

        // o(n) time complexity
        for(int i = 0; i < n; i++)
            a[i] = (5 * i) % n; // Permutation function f(x) = 5x % n
        return a;
    }
}
