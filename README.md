# simple-compressor

A simple compressor based on hoffman compress algorithm.

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

```
file content
    --> content string
        --> decode content string with table
            --> save to file
```