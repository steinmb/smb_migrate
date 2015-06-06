<?php

/**
 * Implements hook_migrate_api().
 */
function smb_migrate_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'content_migration' => array(
        'title' => t('SMB Drupal 6 to Drupal 7 content migration example.'),
      ),
      'taxonomy' => array(
        'title' => t('SMB Drupal 6 to Drupal 7 taxonomy migration example.')
      ),
    ),
  );

  // Specify the DB connection and the source Drupal version.
  $common_arguments = array(
    'source_connection' => 'legacy',
    'source_version' => 6,
    'group_name' => 'content_migration',
    'format_mappings' => array(
      '0' => 'plain_text',
      '1' => 'filtered_html',
      '2' => 'full_html',
      '3' => 'foo',
    ),
  );

  /**
   * Register the user migration.
   * We just use the migrate_d2d D6 migration class as-is.
   */
  $api['migrations']['User'] = $common_arguments + array(
    'description' => t('Migration of users from Drupal 6'),
    'class_name' => 'DrupalUser6Migration',
  );

  /**
   * For vocabulary migrations, source_vocabulary and destination_vocabulary are
   * required arguments. Note that in Drupal 6 vocabularies did not have machine
   * names, so we use the vocabulary ID to uniquely identify them.
   */
  $vocabulary_arguments = array(
    'Tags' => array(
      'description' => t('Migration of Topics terms from Drupal 6'),
      'source_vocabulary' => '1',  // D6 Vocabulary ID
      'destination_vocabulary' => 'tags',
      'group_name' => 'taxonomy',
    ),
    'Tags2' => array(
      'description' => t('Migration of Topics terms from Drupal 6'),
      'source_vocabulary' => '2',  // D6 Vocabulary ID
      'destination_vocabulary' => 'tags2',
      'group_name' => 'taxonomy',
    ),
    'Tags3' => array(
      'description' => t('Migration of Topics terms from Drupal 6'),
      'source_vocabulary' => '3',  // D6 Vocabulary ID
      'destination_vocabulary' => 'tags3',
      'group_name' => 'taxonomy',
    ),
  );

  /**
   * Again, we're using the migrate_d2d class directly.
   * The soft dependency says that while we don't have to run the user migration
   * first, we want to make sure it's listed first so the vocabularies are
   * listed right ahead of the node migrations.
   */
  $common_vocabulary_arguments = $common_arguments + array(
    'class_name' => 'DrupalTerm6Migration',
    'soft_dependencies' => array('User'),
  );

  foreach ($vocabulary_arguments as $migration_name => $arguments) {
    $arguments += $common_vocabulary_arguments;
    $api['migrations'][$migration_name] = $arguments;
  }

  // Register the file migration.
  // source_dir needs to be adjusted to match your file system.
  $api['migrations']['File'] = $common_arguments + array(
    'machine_name' => 'filemigration',
    'description' => t('Import Drupal 6 files'),
    'class_name' => 'SMBFile6Migration',
    'user_migration' => 'User',
    'default_uid' => 1,
    'source_dir' => DRUPAL_ROOT . '/../drupal-6.x-dev',
    'destination_dir' => 'public://legacy_files',
  );

  /**
   * Node migrations - each has its own class derived from the migrate_d2d class,
   * specifying its particular field mappings and transformations. source_type
   * and destination_type are required arguments.
   */
  $node_arguments = array(
    'Page' => array(
      'class_name' => 'PageMigration',
      'description' => t('Migration of page nodes from Drupal 6'),
      'source_type' => 'page',
      'destination_type' => 'page',
    ),
    'Article' => array(
      'class_name' => 'ArticleMigration',
      'description' => t('Migration of article nodes from Drupal 6'),
      'source_type' => 'story',
      'destination_type' => 'article',
    ),
  );

  /**
   * Tell the node migrations where the users are coming from, so they can
   * set up the dependency and resolve D6->D7 uids.
   */
  $common_node_arguments = $common_arguments + array(
      'user_migration' => 'User'
    );

  foreach ($node_arguments as $migration_name => $arguments) {
    $arguments = array_merge_recursive($arguments, $common_node_arguments);
    $api['migrations'][$migration_name] = $arguments;
  }

  return $api;
}
