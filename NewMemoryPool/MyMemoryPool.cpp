#include "MyMemoryPool.hpp"

#include <stdlib.h>
#include <iostream>



MyMemoryPool::~MyMemoryPool()
{
	delete m_pChunkHead;
}

void MyMemoryPool::init(unsigned int blockSize, unsigned int blockNumber)
{
	const unsigned int headerSize = sizeof(m_pChunkHead);
	unsigned int realBlockSize = blockSize + headerSize;

	m_blockNumber = blockNumber;
	m_blockSize = blockSize;

	std::cout << "blockSize : " << blockSize << std::endl;
	std::cout << "header blockSize : " << headerSize << std::endl;
	std::cout << "Real blockSize : " << realBlockSize << std::endl;
	std::cout << "nbBlocks : " << blockNumber << std::endl;
	std::cout << "chunk size : " << blockSize * blockNumber << std::endl;
	std::cout << "dataBlocks : " << (blockNumber - 1) / 2 << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	m_pChunkHead = reinterpret_cast<unsigned char*> (malloc( blockSize * blockNumber));
	if (m_pChunkHead != nullptr)
	{
		m_pHead = reinterpret_cast<unsigned int*> (m_pChunkHead);

		auto p = reinterpret_cast<unsigned int*> (m_pChunkHead);
		for (unsigned int i = 0; i < blockNumber; i++) {
			*p = 1;
			p++;
		}

		p = reinterpret_cast<unsigned int*> (m_pChunkHead);
		auto next_p = reinterpret_cast<unsigned int**>(p);

		for (unsigned int i = 0; i < blockNumber - 2; i += 2) 
		{
			*next_p = p + 2;
			p += 2;
			next_p += 2;
		}

		*next_p = nullptr;

		printMemory();
	}
	
}

void* MyMemoryPool::alloc()
{
	auto p = reinterpret_cast<unsigned int*> (m_pChunkHead);

	/*if (reinterpret_cast<unsigned int*>(*m_pHead) != nullptr)
	{
		auto val = m_pHead + 1;
		auto temp = reinterpret_cast<unsigned int**>(m_pHead);
		m_pHead = reinterpret_cast<unsigned int*> (*m_pHead);
		*temp = nullptr;
		return val;
	}
	else*/
	//{
		for (unsigned int i = 0; i < m_blockNumber - 2; i += 2) {
			if (reinterpret_cast<unsigned int*>(*p) != nullptr) {
				m_pHead = p;
				auto val = m_pHead + 1;
				auto temp = reinterpret_cast<unsigned int**>(m_pHead);
				m_pHead = reinterpret_cast<unsigned int*> (*m_pHead);
				*temp = nullptr;
				return val;
			}
			p += 2;
		}
		unsigned int OldBlockNumber = m_blockNumber - 1;
		std::cout << "Can't alloc because Memory slot is full! Auto Expand Chuck of Memory" << std::endl;
		std::cout << std::endl;
		expand();
		m_pHead += OldBlockNumber;
		auto val = m_pHead + 1;
		auto temp = reinterpret_cast<unsigned int**>(m_pHead);
		m_pHead = reinterpret_cast<unsigned int*> (*m_pHead);
		*temp = nullptr;
		return val;
		//std::cout << "Can't alloc because memory slot is full! Please release some of it" << std::endl;
		//return nullptr;
	//}
}

void MyMemoryPool::release(void* val)
{
	if (val != nullptr)
	{
		std::cout << "Release : " << *reinterpret_cast<unsigned int*>(val) << std::endl;
		auto pHead = reinterpret_cast<unsigned int*>(val) - 1;
		if (reinterpret_cast<unsigned int*>(*pHead) == nullptr)
		{
			m_pHead = pHead;
			auto next_p = reinterpret_cast<unsigned int**>(m_pHead);
			*next_p = m_pHead + 2;
		}
		else
		{
			std::cout << "This slot is already free.." << std::endl;
		}
	}
}



void MyMemoryPool::expand() 
{
	unsigned char* tempChunk = reinterpret_cast<unsigned char*> (malloc(m_blockSize * m_blockNumber));
	auto p = reinterpret_cast<unsigned int*> (m_pChunkHead);
	auto pTemp = reinterpret_cast<unsigned int*> (tempChunk);
	unsigned int oldBlockNumber = m_blockNumber;

	for (unsigned int i = 0; i < m_blockNumber; i++) {
		*pTemp = *p;
		p++;
		pTemp++;
	}

	init(m_blockSize, ((m_blockNumber - 1) * 2) + 1);

	p = reinterpret_cast<unsigned int*> (m_pChunkHead);
	pTemp = reinterpret_cast<unsigned int*> (tempChunk);

	for (unsigned int i = 0; i < oldBlockNumber - 1; i++) {
		*p = *pTemp;
		pTemp++;
		p++;
	}

	printMemory();

}

void MyMemoryPool::printMemory() const
{
	auto p = reinterpret_cast<unsigned int*> (m_pChunkHead);
	bool isFree = true;

	std::cout << "+";
	for (unsigned int i = 0; i < (m_blockNumber - 1) / 2; i++)
	{
		std::cout << "+++";
	}
	std::cout << std::endl;

	std::cout << "|";
	for (unsigned int i = 0; i < m_blockNumber; i++)
	{
		if (i % 2 == 0) 
		{
			if (reinterpret_cast<unsigned int*>(*p) == nullptr)
			{
				isFree = false;
			}
			else
			{
				isFree = true;
			}
		}
		else
		{
			if (isFree)
			{
				std::cout << "  |";
			}
			else
			{
				std::cout << *p << "|";
			}
		}
		p++;
	}
	std::cout << std::endl;

	std::cout << "+";
	for (unsigned int i = 0; i < (m_blockNumber - 1) / 2; i++)
	{
		std::cout << "+++";
	}
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
}