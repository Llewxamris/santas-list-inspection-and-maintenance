<?php
// errorMessage is set to empty string to start.
$errorMessage = '';
// An associative array of all of the fields on the page and their data.
$values = array(
                "personId"      => "",
                "firstName"     => "",
                "lastName"      => "",
                "age"           => "",
                "curList"       => "",
                "city"          => "",
                "details"       => "",
                "dateUpdated"   => "" 
               );

 function main() {
    // The main function that calls all the other functions.
    // Returns TRUE if no errors are found, and FALSE if errors are found.
    global $values;
    global $errorMessage; 
    global $values;

    // Get user input and add it to the values array.
    $values = array(
                    "personId"  => $_POST['personId'],
                    "firstName" => $_POST['firstName'],
                    "lastName"  => $_POST['lastName'],
                    "age"       => $_POST['age'],
                    "curList"   => $_POST['curList'],
                    "city"      => $_POST['city'],
                    "details"   => $_POST['details']
                    );

    $success = TRUE;
    $errorEnding = ' Please enter a proper value' . '<br />';
    
    foreach($values as $key => $input) {
        // Trims each value
        $values[$key] = trim($input);
    }

    if($values['personId'] !== '') {
        // If the personId is not new...
        if(!validateNumExists($values['personId'])) {
            // ...and if the number entered does not exist
            $errorMessage .= 'Personal ID does not exist. To create a new user, leave the Personal ID empty. <br />';
            $success = false;
        }
    } 

    // Validates if all other fields exist
    if (!validateExists($values['firstName'])) {
        $errorMessage .= 'First name is empty.' . $errorEnding;
        $values['firstName'] = '';
        $success = false;
    }

    if (!validateExists($values['lastName'])) {
        $errorMessage .= 'Last name is empty.' . $errorEnding; 
        $values['lastName'] = '';
        $success = false;
    }

    if (!validateExists($values['age'])) {
        $errorMessage .= 'Age is empty.' . $errorEnding; 
        $success = false;
        $values['age'] = '';
    }

     if (!validateExists($values['city'])) {
         $errorMessage .= 'City is empty.' . $errorEnding;
         $success = false;
         $values['city'] = '';
     }
    
     // If there were no issues, write to the file
     // Else, return the fail
     if ($success) {
        writeToFile();
        return $success; 
    } else {
        return $success;
    }
}
 

function validateExists($data) {
    // Makes sure the data is not empty.
    if ($data != '') {
        return true;
    } else {
        return false;
    }
}

function hasError($data) {
    // Determins if the data had an error or not.
    global $values;
    if($data == '') {
        return 'error';
    } else {
        return "";
    }
}

function writeToFile() {
    // Writes everything in the array $values to the file accounts.txt
    global $values;
    $foundReplace = false;
    $fileName = './List/SantaList.json';
    $jsonArray = array();
    $currPerson = array (     '-id'  => $values['personId'],
                        'firstName'  => $_POST['firstName'],
                         'lastName'  => $_POST['lastName'],
                              'age'  => $_POST['age'],
                             'city'  => $_POST['city'],
                          'curList'  => $_POST['curList'],
                          'details'  => $_POST['details'],
                      'dateUpdated'  => date('Y-m-d'));

    $jsonFile = file_get_contents($fileName);
    $jsonArray = json_decode($jsonFile, true);
    
    if ($currPerson['-id'] === '') {
        // If the user has not entered an id...
        // ...creates a new id, and increments
        // the id file
        $currPerson['-id'] = getNewNumber();
        addOneToIdList();
        array_push($jsonArray['person'], $currPerson);
    } else { 
        // Update the User
        foreach ($jsonArray['person'] as &$key) {
            if ($key['-id'] === $currPerson['-id']) {
                foreach ($key as $input => &$output) {
                    $output = $currPerson[$input];
                }   
            } 
        }
    }


    $jsonFile = json_encode($jsonArray, JSON_PRETTY_PRINT);
    file_put_contents($fileName, $jsonFile);

    return true;
}

function fillForms() {
    // Sets all the values in the form to previously entered values
    global $values;
    $fileName = './List/SantaList.json';
    $jsonFile = file_get_contents($fileName);
    $jsonArray = json_decode($jsonFile, true);
    $found = FALSE;

    foreach ($jsonArray['person'] as $value)
    {
        if ($value['-id'] == trim($_POST['personId'])) {
            $values = array("personId"  => trim($_POST['personId']),
                            "firstName" => $value['firstName'],
                            "lastName"  => $value['lastName'],
                            "age"       => $value['age'],
                            "curList"   => $value['curList'],
                           "city"      => $value['city'],
                            "details"   => $value['details']);
        }
    }
    return $found;
}

function validateNumExists($inputId) {
    // Searched through the idList, and checks if the number does not exists
    $jsonArray = json_decode(file_get_contents('./List/idList.json'), true);

    foreach ($jsonArray as $number) {
        if ($number === $inputId) {
            return true;
        }
    }
    return false;
}

function getNewNumber() {
    // Finds the largest number, and adds 1, then returns that new number;
    $jsonArray = json_decode(file_get_contents('./List/idList.json'), true);
    $largestNumber = 0;

    foreach ($jsonArray as $number) {
        if ($number > $largestNumber) {
            $largestNumber = $number;
        } 
    }    

    return $largestNumber + 1;
}

function addOneToIdList() {
    // Adds a new number to the list that is one larger than the largest number
    $jsonArray = json_decode(file_get_contents('./List/idList.json'));
    array_push($jsonArray, getNewNumber());
    file_put_contents('./List/idList.json', json_encode($jsonArray));
}
