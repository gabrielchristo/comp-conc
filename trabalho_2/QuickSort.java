import java.util.Random;
import java.util.Arrays;

// classe responsavel pela inicializacao do vetor de inteiros, thread pool e runnable do algoritmo
class QuickSort
{
	private static final int maxArrayValue = 100; // valor maximo sorteado pelo random
	private Random random; // objeto random
	public int[] array; // vetor de inteiros
	
	// construtor
	public QuickSort(int arraySize)
	{
		this.random = new Random();
		
		try {
			this.array = new int[arraySize];
		} catch(OutOfMemoryError err) {
			System.out.println("Sem memoria disponivel para alocar array desse tamanho");
			System.exit(1);
		}
		
		this.initArrayWithRandomValues();
	}
	
	// inicializa array com valores aleatorios
	void initArrayWithRandomValues()
	{
		for(int i = 0; i < this.array.length; i++)
			this.array[i] = random.nextInt(maxArrayValue);
	}
	
	// imprime os valores do array
	public void printArray()
	{
		System.out.println(Arrays.toString(this.array));
	}
	
	public static void main(String[] args)
	{
		// checando tamanho do vetor de argumentos
		if(args.length != 2){
			System.out.println("Usage: java QuickSort arraySize threadsNumber");
			System.exit(1);
		}
		
		// convertendo argumentos (strings) para inteiros
		int arraySize = Integer.parseInt(args[0]);
		int threadsNumber = Integer.parseInt(args[1]);
		
		// criando objeto thread pool
		ThreadPool threadPool = new ThreadPool(threadsNumber);
		
		// criando objeto quicksort (vai criar array de tamanho desejado)
		QuickSort qs = new QuickSort(arraySize);
		
		// imprimindo array sorteado
		//qs.printArray();
		
		// checando tempo de inicio da ordenacao
		long start = System.currentTimeMillis();
		
		// runnable principal
		AlgorithmRunnable ar = new AlgorithmRunnable(qs.array, 0, arraySize - 1, threadPool);
		ar.start();
		
		// quando o algoritmo finalizar encerramos o thread pool
		while(!ar.isFinished()) {
			try {
                Thread.sleep(1); // dormindo 1ms
            } catch (Exception e) {
                e.printStackTrace();
            }
		}
		// parando thread pool
		threadPool.stop();
		
		// checando tempo de fim da ordenacao
		long end = System.currentTimeMillis();
		System.out.printf("Elapsed time: %d ms\n", end - start);
		
		// mostrando array ordenado
		//qs.printArray();
		
	}
	
}