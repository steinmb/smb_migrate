<?php

/**
 * Implements hook_migrate_api().
 */
function dhs_migrate_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'content_migration' => array(
        'title' => t('SMB Drupal 6 to Drupal 7 migration example.'),
      ),
    ),
  );

  // Specify the DB connection and the source Drupal version.
  $common_arguments = array(
    'source_connection' => 'legacy',
    'source_version' => 6,
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
    'ImageTags' => array(
      'description' => t('Migration of photo terms from Drupal 6'),
      'source_vocabulary' => '5',  // D6 Vocabulary ID
      'destination_vocabulary' => 'bilde',
    ),
    'Topics' => array(
      'description' => t('Migration of Topics terms from Drupal 6'),
      'source_vocabulary' => '1',  // D6 Vocabulary ID
      'destination_vocabulary' => 'tags',
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


  /**
   * Node migrations - each has its own class derived from the migrate_d2d class,
   * specifying its particular field mappings and transformations. source_type
   * and destination_type are required arguments.
   */
  $node_arguments = array(
    'Album' => array(
      'class_name' => 'AlbumMigration',
      'description' => t('Migration of photo album nodes from Drupal 6'),
      'source_type' => 'fotoalbum',
      'destination_type' => 'fotoalbum',
    ),
    'Image' => array(
      'class_name' => 'ImageMigration',
      'description' => t('Migration of bilde nodes from Drupal 6'),
      'source_type' => 'bilde',
      'destination_type' => 'bilde',
      'dependencies' => array('ImageTags', 'Album'),
    ),
    'Article' => array(
      'class_name' => 'ArticleMigration',
      'description' => t('Migration of article nodes from Drupal 6'),
      'source_type' => 'page',
      'destination_type' => 'innhold',
      'dependencies' => array(),
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
