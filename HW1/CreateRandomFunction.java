// Oscar Esparza
// 16 September 2018
// CSC 152
// randomFunction.java

import java.util.Random;
class Main {
    public static void main(String[] args) {
        int n = 11; // size of set
        int[] a;    // a[x] holds the value that x maps to

        a = createRandomFunction(n);

        for(int i = 0; i < n; i++){
            System.out.print(a[i]);
            System.out.print(" ");
        }
    }

    public static int[] createRandomFunction(int n){
        int[] a;
        a = new int[n];
        Random rand = new Random();

        // o(n) time complexity
        for(int i = 0; i < n; i++)
            a[i] = rand.nextInt(n); //random number generator
        return a;
    }
}