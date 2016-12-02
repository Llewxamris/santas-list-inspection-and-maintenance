<?php
/*
 * Retrieves a JSON object based on the parameter "which".
 */
$list = $_GET['which']; // Get the list type to search for

const FILE_NAME = './List/SantaList.json'; // Constant for the name of the file

$json_string = file_get_contents(FILE_NAME) 
    or die ('Error: Cannot get JSON file'); // Retrieve the file, or end

$json_file = json_decode($json_string, true); // Decode the JSON file

$return_json = '{ "person": ['; // Opening JSON tags, and "person" array key

foreach ($json_file['person'] as $value) {
    // For each key in the person array:
    if ($value['currList'] == $list) {
        // If the currList value matches the list, add it's content into the
        // return_json string.
        // REFACTOR: This big append strings could be replaced with another
        // foreach loop.
        $return_json .= "{";
        $return_json .= "\"-id\": \"" .  $value['-id'] . "\",";
        $return_json .= "\"lastName\": \"" .  $value['lastName'] . "\",";
        $return_json .= "\"firstName\": \"" .  $value['firstName'] . "\",";
        $return_json .= "\"age\": \"" .  $value['age'] . "\",";
        $return_json .= "\"currList\": \"" .  $value['currList'] . "\",";
        $return_json .= "\"details\": \"" .  $value['details'] . "\",";
        $return_json .= "\"dateUpdated\": \"" .  $value['dateUpdated'] . "\"";
        $return_json .= "},";
    }
}

$return_json = rtrim($return_json, ","); // Remove the trailing comma
$return_json .= "]}"; // Closing JSON tags

// Set the response headers content type and length
header("Content-Type: application/json");
header("Content-Length: " . strlen($return_json));

echo $return_json;
