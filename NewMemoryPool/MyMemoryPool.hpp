#pragma once
class MyMemoryPool
{

private:
	unsigned int m_blockNumber;
	unsigned int * m_pHead;
public:
	MyMemoryPool() : m_blockNumber(0) {};
	~MyMemoryPool();

	unsigned char* m_pChunkHead;

	void init(unsigned int blockSize, unsigned int blockNumber);
	void* alloc();
	void release(void* p);

	void printMemory() const;
};

