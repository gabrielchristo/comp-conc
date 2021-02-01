
/*
 * Classe para modelar o buffer que armazenara os produtos
 * */
class Buffer
{
    //Definindo vetor de inteiros
    private Integer[] productsVector;

    //Indice da posicao apropriada para se retirar/inserir produtos
    private Integer positionIndex;
	
	//Quantidade atual de elementos criados
    private Integer currentNumberProduct;
	
	//Quantidade de elementos que precisam ser criados
    public Integer numberTotalProduct;

    //Construtor da classe
    public Buffer(Integer sizeProductsVector, Integer numberTotalProduct)
    {
        this.productsVector = new Integer[sizeProductsVector];
        this.positionIndex = 0;
		this.currentNumberProduct = 0;
		this.numberTotalProduct = numberTotalProduct;
    }

    //Metodo para retornar tamanho do buffer
    public Integer size()
    {
        return this.productsVector.length;
    }

    //Verifica se vetor esta vazio
    public synchronized boolean isEmpty()
    {
        return this.positionIndex == 0;
    }

    //Verifica se vetor esta cheio
    public synchronized boolean isFull()
    {
        return  this.positionIndex == this.productsVector.length;
    }

    //Metodo para inserir produtos dentro do buffer
    public synchronized void insert(Integer product)
    {
        try
        {
            //Verificando se buffer nao esta cheio
            while(this.isFull())
                this.wait();

            //Inserindo produto na posicao apropriada
            this.productsVector[this.positionIndex] = product;

            //Atualizando indice do buffer
            this.positionIndex++;

            //Liberando as demais threads
            this.notifyAll();
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
            return;
        }
    }

    //Metodo para remover elementos do buffer
    public synchronized Integer remove()
    {
        try
        {
            //Verificando se buffer nao esta vazio
            while(this.isEmpty())
                this.wait();

            //Atualizando indice do buffer
            this.positionIndex--;

            //Removendo produto na posicao apropriada
            Integer product = this.productsVector[this.positionIndex];

            //Liberando as demais threads
            this.notifyAll();

            //Retornando elementos
            return  product;
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
            return null;
        }
    }

    //Metodo para imprimir elementos do buffer
    public void print()
    {
        System.out.println("=====");
        for(Integer currentProduct : this.productsVector)
            System.out.printf("Inteiro: %d\n", currentProduct);
    }
	
	//Metodo para atualizar o quantidade atual de produtos criados
    public synchronized void updateCurrentNumberProduct()
    {
        this.currentNumberProduct++;
    }
	
	//Getter para o campo currentNumberProduct
    public synchronized Integer getCurrentNumberProduct()
    {
        return this.currentNumberProduct;
    }
	
}
