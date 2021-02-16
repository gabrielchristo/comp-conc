import java.util.Random;
import java.util.Arrays;

class QuickSort
{
	private static final int maxArrayValue = 50; ///< valor maximo sorteado pelo random
	private Random random; ///< objeto random
	private int[] array; ///< vetor de inteiros
	
	// construtor
	public QuickSort(int arraySize)
	{
		this.random = new Random();
		this.array = new int[arraySize];
		this.initArrayWithRandomValues();
	}
	
	// inicializa array com valores aleatorios
	void initArrayWithRandomValues()
	{
		for(int i = 0; i < this.array.length; i++)
			this.array[i] = random.nextInt(maxArrayValue);
	}
	
	// imprime os valores do array
	void printArray()
	{
		System.out.println(Arrays.toString(this.array));
	}
	
	
	public static void main(String[] args)
	{
		// checando tamanho do vetor de argumentos
		if(args.length != 1){
			System.out.println("Usage: java QuickSort arraySize");
			System.exit(1);
		}
		
		// criando objeto quicksort (vai criar array de tamanho desejado)
		int arraySize = Integer.parseInt(args[0]);
		QuickSort qs = new QuickSort(arraySize);
		qs.printArray();
		
		
	}
	
	
	
}