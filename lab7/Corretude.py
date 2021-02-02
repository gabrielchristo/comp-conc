
class CheckingModule():

	def __init__(self):
		self.size = 0
		self.freePos = 0
		
	# inicializa o tamanho do buffer e posicoes livres
	def setSize(self, length):
		self.size = length
		self.freePos = length
		
	def eventoProdutorProduziu(self, idProdutor):
		if(bufferCheio()):
			print("Erro: produtor ", idProdutor, " produziu com buffer cheio")
		self.freePos -= 1
		
	def eventoConsumidorConsumiu(self, idConsumidor):
		if(bufferVazio()):
			print("Erro: consumidor ", idConsumidor, " consumiu com buffer vazio")
		self.freePos += 1
		
	def eventoConsumidorBloqueou(self, idConsumidor):
		if(not bufferVazio()):
			print("Erro: consumidor ", idConsumidor, " bloqueou sendo que o buffer nao esta vazio")
		
	def eventoProdutorBloqueou(self, idProdutor):
		if(not bufferCheio()):
			print("Erro: produtor ", idProdutor, " bloqueou sendo que o buffer tem espaco disponivel")
		
	def bufferVazio(self) -> bool:
		if(self.freePos < self.size):
			print("Erro: buffer nao esta vazio")
			return False
		return True
		
	def bufferCheio(self) -> bool:
		if(self.freePos > 0):
			print("Erro: buffer nao esta cheio")
			return False
		return True
		