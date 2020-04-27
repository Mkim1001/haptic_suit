<?php
$to = 'in@rommar.in.ua'; //Change to your e-mail
$subject = 'Email from my site';

$name = $_POST['name'];
$service = $_POST['service'];
$budget = $_POST['budget'];
$email = $_POST['email'];

$name = filter_var($_POST['name'], FILTER_SANITIZE_STRING);
$service = filter_var($_POST['service'], FILTER_SANITIZE_STRING);
$budget = filter_var($_POST['budget'], FILTER_SANITIZE_STRING);
$email = filter_var($_POST['email'], FILTER_SANITIZE_EMAIL);

$output = '';
$process = true;

if (strlen($name) <= 0) {
	$output[] = array(
		'status' => 0,
		'field' => "name",
		'message' => "Name is too short"
	);
	$process = false;
}

if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
	$output[] = array(
		'status' => 0,
		'field' => "email",
		'message' => "Enter corrent e-mail."
	);
	$process = false;
}


if ($process) {
	$full_message .= 'Name: '.$name."\n";
	$full_message .= 'E-mail: '.$email."\n";
	$full_message .= 'Service: '.$service."\n";
	$full_message .= 'Budget: '.$budget."\n";

	$headers .= 'From: '.$email."\r\n";
	$headers .= 'Reply-To: '.$email."\r\n";
	$headers .= 'X-Mailer: PHP/'.phpversion();

	if (mail($to, $subject, $full_message, $headers)) {
		$output[] = array(
			'status' => 1,
			'field' => "send",
			'message' => 'Hey, Amigo! We will contact you later, thanx.'
		);
	} else {
		$output[] = array(
			'status' => 0,
			'field' => "send",
			'message' => 'Could not send mail! Please check your PHP mail configuration.'
		);
	}
}
$response = json_encode($output);
die($response);
?>
