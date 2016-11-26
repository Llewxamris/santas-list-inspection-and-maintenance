<?php
// errorMessage is set to empty string to start.
$errorMessage = '';
// An associative array of all of the fields on the page and their data.
$values = array("personalId" => $_POST['personalId'],
                "firstName" => $_POST['firstName'],
                "lastName" => $_POST['lastName'],
                "age" => $_POST['age'],
                "curList" => $_POST['curList'],
                "details" => $_POST['details']);

 function main() {
    // The main function that calls all the other functions.
    // Returns TRUE if no errors are found, and FALSE if errors are found.
    global $errorMessage; 
    global $values;
    $success = TRUE;
    $errorEnding = " Please enter a proper value" . "<br>";
    
    foreach($values as $key => $input) {
        // Trims each value
        $values[$key] = trim($input);
    } 

    if(validateExists($values['personalId']) == FALSE) {
        $errorMessage .= "Personal Identification  is empty. $errorEnding";
        $values['personalId'] = "";
        $success = FALSE;
    }

    if(validateExists($values['firstName']) == FALSE) {
        $errorMessage .= "First name is empty. $errorEnding";
        $values['firstName'] = "";
        $success = FALSE;
    }

    if(validateExists($values['lastName']) == FALSE) {
        $errorMessage .= "Last name is empty." . $errorEnding; 
        $values['lastName'] = "";
        $success = FALSE;
    }

    if(validateExists($values['age']) == FALSE) {
        $errorMessage .= "Age is empty." . $errorEnding; 
        $success = FALSE;
        $values['age'] = "";
    }

    if ($success) {
        writeToFile();
        return $success; 
    } else {
        return $success;
    }
}
 

function validateExists($data) {
    // Makes sure the data is not empty.
    if($data != '') {
        return TRUE;
    } else {
        return FALSE;
    }
}

function hasError($data) {
    // Determins if the data had an error or not.
    global $values;
    if($data == "") {
        return "error";
    } else {
        return "";
    }
}

function writeToFile() {
    // Writes everything in the array $values to the file accounts.txt
    global $values;
    $textToFile = "";
    foreach ($values as $key => $input) {
        if($key != "confirmPass") {
            $textToFile .= $input . "~";
        }
    }
    $textToFile .= "\r\n";
    file_put_contents("./accounts.txt", $textToFile, FILE_APPEND);
}
