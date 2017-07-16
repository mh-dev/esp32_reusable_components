# Reusable components for the ESP32
This repository demonstrates a simple setup that allows to develop multiple components that can be used
in multiple applications.

# Preconditions
* SDK [ESP-IDF](https://github.com/espressif/esp-idf) is cloned into a local folder
* Envrionment variable `IDF_PATH` has been set to the SDK location

# Setup
The repository consists of the custom components and an application that uses it.

## Custom components
They are located in the `custom-components` folder. The components itself are located in the `components` subdirectory. This example contains the `awesome_compontent` and contains a simple method that adds two numbers. 

### Structure of a component
A component is a folder in `custom-components/components` every component should be located in this folder. See the `awesome-component` as an example.
```
my_component/
    include/
        my_code.h
    src/
        my_code.c
    test/
        component.mk
            COMPONENT_ADD_LDFLAGS = -Wl,--whole-archive -l$(COMPONENT_NAME) -Wl,--no-whole-archive
        test_my_code.c
    component.mk
        COMPONENT_ADD_INCLUDEDIRS := include
        COMPONENT_SRCDIRS := src
```
### Execute custom component tests
This is based on [unit-test-app](https://github.com/espressif/esp-idf/tree/master/tools/unit-test-app). It consist of a standard `Makefile`, `main/main.c` and `main/component.mk`. There is usually no need to change anything here. 

Before we can execute tests make sure to set environment variable `EXTRA_COMPONENT_DIRS` to `"$IDF_PATH/tools/unit-test-app/components"` this makes the unity framework available for the build system. Another option is to copy the `unity` component from this folder to your components folder. 

#### Execute the tests
Open the shell and navigate to `repository/custom-components` and invoke `make flash TEST_COMPONENTS='component_name1 other_component' monitor`. This compiles everything, flashes it to your esp and starts monitoring once flashing is completed. The shell should display a menu of all available tests once bootstrapping is completed. More details see [Testing](http://esp-idf.readthedocs.io/en/latest/api-guides/unit-tests.html?highlight=Testing)

Example for this repository
`make flash TEST_COMPONENTS='awesome_component' monitor`

## Application
Of course we want to use our components in our applications. These applications can be located anywhere. This repository has its example application `app` located in the repository for demonstration purpose. This is a standard esp-idf application. Nothing special here. 

### Make custom components available
The build system does not know anything about your custom components right now. This can be changed similar to the way we made the unity component availabel. 

To do that change the `EXTRA_COMPONENT_DIRS` to `"$IDF_PATH/tools/unit-test-app/components repositoryPath/custom-components/components"`
 make sure to replace *repositoryPath* to the location of your folder. 
 
## Example environment variables
```
export IDF_PATH="pathToSDK/"
export EXTRA_COMPONENT_DIRS="$IDF_PATH/tools/unit-test-app/components /pathToMyComponents/"
```
