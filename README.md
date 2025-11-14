# 🥀Petals & Spores🍄

```
(Obiectul tău principal, să zicem "Game")
   |
   +--> [ ECS::Registry ]
          (Obiect)
          |
          +--> [ _availableEntities (std::queue) ]
          |
          +--> [ m_ComponentArrays (std::unordered_map) ]
                 |
                 |-- Cheie: [ typeid(Transform) ]
                 |    Valoare: std::unique_ptr --+
                 |                               |
                 |-- Cheie: [ typeid(Sprite) ]   |
                 |    Valoare: std::unique_ptr --+---+
                 |                               |   |
                 '-- Cheie: [ typeid(Rigidbody) ]|   |
                      Valoare: std::unique_ptr --+---+---+
                                                 |   |   |
                                                 |   |   |
----------------- (Granița Stack / Heap) -------------------------
                                                 |   |   |
(MEMORIA HEAP)                                   |   |   |
                                                 |   |   |
    +--------------------------------------------+   |   |
    |                                                |   |
    v                                                |   |
    [ ComponentArray<Transform> (Obiect) ]           |   |
    |                                                |   |
    |  +-> [ m_HasComponentMask (std::bitset) ]      |   |
    |  |   | 0 | 1 | 0 | 1 | ... | (MaxEntities biți)|   |
    |  |                                             |   |
    |  +-> [ m_ComponentArray (std::array) ]         |   |
    |      | T[0] | T[1] | T[2] | T[3] | ... | T[Max]|   |
    |     <--------- BLOC CONTIGUU DE MEMORIE ---->  |   |
    |                                                |   |
    +------------------------------------------------+   |
                                                         |
    +----------------------------------------------------+
    |
    v
   [ ComponentArray<Sprite> (Obiect) ]
   |
   |  +-> [ m_HasComponentMask (std::bitset) ]
   |  |   | 1 | 1 | 0 | 0 | ... |
   |  |
   |  +-> [ m_ComponentArray (std::array) ]
   |      | S[0] | S[1] | S[2] | S[3] | ... | S[Max] |
   |      <--------- BLOC CONTIGUU DE MEMORIE ---->
   |
   +----------------------------------------------------+
                                                        |
   +----------------------------------------------------+
                                                        v
                                              (Similar pt Rigidbody)
```
