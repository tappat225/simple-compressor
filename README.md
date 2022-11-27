# simple-compressor

A simple compressor based on huffman compress algorithm.

## Design

**Encode**

```
file content

    --> content string

        --> charater feq table

            --> reform in seq order

                --> generate hoffman tree

                    --> generate hoffman compress table

                        --> save table

                        --> encode content string with table

                            --> save to file
```

**Decode**

two ways:

1.using huffman tree from encoding part.

```
file content
    --> content string
        --> decode content string with huffman tree
            --> save to file
```

2.using character table but it requies the compressed bit stream must be divied by a special sign from bit to bit.

```
file content
    --> content string
        --> decode content string with table
            --> save to file
```
