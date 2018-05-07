import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class java_matrix{
    public static void main(String[] args){

        //starttime
        long start = System.currentTimeMillis();

        //the size of matrix
        int maxn = 300;
        
        int arr1[][] = new int[maxn][maxn];
        int arr2[][] = new int[maxn][maxn];
        int arr3[][] = new int[maxn][maxn];

        //initialize
        Random rand = new Random();
        for(int i = 0; i < maxn; i++)
        {
            for(int j = 0; j < maxn; j++)
            {
                arr1[i][j] = rand.nextInt(100);
                arr2[i][j] = rand.nextInt(100);
            }
        }

        //mul
        for(int i = 0; i < maxn; i++)
        {
            for(int j = 0; j < maxn; j++)
            {
                for(int k = 0; k < maxn; k++)
                {
                    arr3[i][j] += arr1[i][k] * arr2[k][j];
                }
            }
        }

        //output
        /*
        for(int i = 0; i < maxn; i++)
        {
            for(int j = 0; j < maxn; j++)
            {
                System.out.print(arr3[i][j] + " ");
            }
            System.out.print("\n");
        }
        */

        //endtime
        long end = System.currentTimeMillis();
        System.out.println("java running time:" + (end - start) + "ms");
    }
}