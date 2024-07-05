# SearchSystem
## Project Description
This project is an implementation of a search engine in C++. The engine's operating principles include indexing text files and performing search queries on them. The user can submit queries via JSON files, and the search results are returned in JSON format, ordered by relevance.

## Stack of technologies used
- **Programming language:** C++
- **Development environment:** VSCode
- **Compiler:** MinGW
- **Build system:** CMake
- **Libraries**:
    - JSON for data serialization
    - Google Test for Unit Testing

## How to run a project locally
### Requirements
- Installed MinGW compiler
- VSCode or any other convenient IDE
- Installed CMake
### Startup instructions

1. **Install the required software:**
   - Download and install the MinGW compiler from [official site](http://www.mingw.org/).
   - Download and install the VSCode from [official site](https://code.visualstudio.com/).
   - Download and install the CMake from [official site](https://cmake.org/download/).

2. **Open the project in VSCode**
3. **Build project**
   JSON files: Before running the application, make sure that the configuration and request files are located in the project root directory:
   - **Configuration file:** config.json
   - **Request file:** requests.json
     
Example contents of the **config.json** file:
```
{
    "config": {
        "name": "SearchSystem",
        "version": "1.0",
        "max_responses": 5
    },
    "files": ["file1.txt", "file2.txt"]
}
```
- "max_response" contains the number of relevant documents displayed for one request
- "files" contains the path to the files that will be searched

Example contents of the **requests.json** file:
```
{
    "requests": ["hello", "world"]
}
```
- "requests" contains the words that will be searched for

The search results will be written to the file **answers.json**

