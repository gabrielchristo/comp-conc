
class CheckingModule():

	def __init__(self):
		self.size = 0
		self.freePos = 0
		
	# inicializa o tamanho do buffer e posicoes livres
	def setSize(self, length):
		self.size = length
		self.freePos = length
		print("Recebido length ", length)
		
	def eventoProdutorProduziu(self):
		if(self.freePos <= 0):
			print("Erro: produtor produziu com buffer cheio")
		self.freePos -= 1
		
	def eventoConsumidorConsumiu(self):
		if(self.freePos == self.size):
			print("Erro: consumidor consumiu com buffer vazio")
		self.freePos += 1
		
	def eventoConsumidorBloqueou(self):
		if(self.freePos < self.size):
			print("Erro: consumidor bloqueou sendo que o buffer nao esta vazio")
		
	def eventoProdutorBloqueou(self):
		if(self.freePos > 0):
			print("Erro: produtor bloqueou sendo que o buffer tem espaco disponivel")
		
	
		